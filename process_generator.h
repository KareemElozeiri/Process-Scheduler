#include "headers.h"


AlgorithmType algo = SJF;
int processesCount = 0;

//==================functions definations====================//
void startClk();
void startScheduler();


//=================functions implementation=================//
void startClk(){
    pid_t pid = fork();

    if(pid==-1){
        perror("Error while forking to start the clk");
        exit(FAILURE_CODE);
    }
    else if(pid==0){
        char *const paramList[] = {"./clk.out", NULL};
        execv("./clk.out", paramList);
        exit(FAILURE_CODE);
    }

}

void startScheduler(){
    pid_t pid = fork();

    if(pid==-1){
        perror("Error while forking to start the scheduler");
        exit(FAILURE_CODE);
    }
    else if(pid==0){

        char stringAlgo[5];
        char stringProcessesCount[10];

        sprintf(stringAlgo, "%d", algo);
        sprintf(stringProcessesCount, "%d", processesCount);
        char *const paramList[] = {"./scheduler.out", stringAlgo, stringProcessesCount, NULL};


        execv("./scheduler.out", paramList);
        

        exit(FAILURE_CODE);
    }

}