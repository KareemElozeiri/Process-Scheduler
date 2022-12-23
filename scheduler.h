#pragma once 
#include "headers.h"

AlgorithmType algo;
int processesCount;


//============ Functions  Definations    =====================//

//process operations
int forkNewProcess();
void startProcess();
void stopProcess();



//communication with process_generator
void recvProcess();

//-------------- Scheduling Algorithms ------------//
void runPHPF();
void runSRTN();
void runSJF();
//------------------------------------------------//

void runAlgo(); // runs choosen algo by the user in process generator



//hanlder for user defined signal
void handleUser1(int signum);

// for clearing on exit
void clearResources(); 


//================ Functions Implementations ===============//



int forkNewProcess(int execution_time){
    pid_t schedulerPid = getpid();
    pid_t processPid = fork();

    if(processPid==-1){
        perror("Error while forking process!");
        exit(FAILURE_CODE);
    }
    else if(processPid==0){
        char stringExecutionTime[5] = {0};
        char stringSchedulerPid[7] = {0};
        char stringClkValue[7] = {0};
        sprintf(stringSchedulerPid, "%d", schedulerPid);
        sprintf(stringExecutionTime, "%d", execution_time);
        sprintf(stringClkValue, "%d", getClk());
        char *const paramList[] = {"./process.out", stringExecutionTime, stringSchedulerPid, stringSchedulerPid,NULL};
        execv("./process.out", paramList);
        
        //if it executes what is under this line, then execv has failed
        perror("Error in execv'ing to clock");
        exit(EXIT_FAILURE);
    }

    return processPid;
}


void recvProcess(){
    ProcessParameters recPrc;
    PCB* prc;
    
    while(msgQueueRcvPrc(&recPrc) != -1){
        //allocating memory for prc
        prc = (PCB*) malloc(sizeof(PCB));

        //extrating PCB obj parameters from the recieved object
        prc->id = recPrc.process_id;
        prc->arrival_time =  recPrc.arrival_time;
        prc->priority = recPrc.priority;
        prc->execution_time = recPrc.execution_time;
        prc->remaining_time = recPrc.execution_time;
        prc->start_time = -1;


        //enqueue to the PCB queue
        //enqueue(prc);

    }
}

void runPHPF(){

}


void runSRTN(){

}

void runSJF(){
    recvProcess();
    
}

void runAlgo(){
    switch(algo){
        case PHPF:
            runPHPF();
            break;
        case SRTN:
            runSRTN();
            break;
        case SJF:
            runSJF();
            break;
    }
}


void handleProcessArrival(int signum){
    recvProcess();
    runAlgo();
}
