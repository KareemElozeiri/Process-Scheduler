#pragma once 
#include <stdio.h>      //if you don't use scanf/printf change this include
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef short bool;
#define true 1
#define false 0
#define SHKEY 300
#define FAILURE_CODE -1
#define MSG_QUEUE_KEY 2001
int msgQueueId;



typedef enum AlgorithmType{
    PHPF,
    SRTN,
    SJF
} AlgorithmType;

typedef enum ProcessState {
    RUNNING, 
    WAITING,
} ProcessState;


typedef struct ProcessParameters{
    int process_id;
    int arrival_time;
    int execution_time;
    int priority;

}ProcessParameters;


typedef struct PCB{
    int id; // id from the file
    pid_t process_id;
    ProcessState process_state;
    int execution_time;
    int waiting_time;
    int remaining_time;
}PCB;

typedef struct Node
{
    PCB *data;
    int priority;
    struct Node *next;
}Node;

///==============================
//don't mess with this variable//
int * shmaddr;                 //
//===============================



int getClk()
{
    return *shmaddr;
}


/*
 * All process call this function at the beginning to establish communication between them and the clock module.
 * Again, remember that the clock is only emulation!
*/
void initClk()
{
    int shmid = shmget(SHKEY, 4, 0444);
    while ((int)shmid == -1)
    {
        //Make sure that the clock exists
        printf("Wait! The clock not initialized yet!\n");
        sleep(1);
        shmid = shmget(SHKEY, 4, 0444);
    }
    shmaddr = (int *) shmat(shmid, (void *)0, 0);
}


/*
 * All process call this function at the end to release the communication
 * resources between them and the clock module.
 * Again, Remember that the clock is only emulation!
 * Input: terminateAll: a flag to indicate whether that this is the end of simulation.
 *                      It terminates the whole system and releases resources.
*/

void destroyClk(bool terminateAll)
{
    shmdt(shmaddr);
    if (terminateAll)
    {
        killpg(getpgrp(), SIGINT);
    }
}


//function initiating the message queue between the process generator
void initMsgQueue(){
    msgQueueId = msgget(MSG_QUEUE_KEY, IPC_CREAT|0644);

    if(msgQueueId==-1){
        perror("Error in creating the message queue");
        exit(FAILURE_CODE);
    }
}

//function destry the message queue between the process generator
void destroyMsgQueue(){
    int destroy_result = msgctl(msgQueueId, IPC_RMID, (void *)0);

    if(destroy_result==-1){
        perror("Error while destroying the Message Queue");
        exit(FAILURE_CODE);
    }

}

//message queue operations (send, recieve) process data

void msgQueueSendPrc(ProcessParameters* prc){
    int send_value = msgsnd(msgQueueId, prc, sizeof(ProcessParameters), !IPC_NOWAIT);

    if(send_value==-1){
        perror("Error sending process to scheduler");
        exit(FAILURE_CODE);
    }
    
}

ssize_t msgQueueRcvPrc(ProcessParameters* prc){
    return msgrcv(msgQueueId, prc, sizeof(ProcessParameters), 0, IPC_NOWAIT);
}

