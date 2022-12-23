#include "headers.h"

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
        execv("./clk.out",NULL);
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
        execv("./scheduler.out",NULL);
        exit(FAILURE_CODE);
    }

}