#pragma once 
#include "headers.h"


AlgorithmType algo;
int processesCount;


//============ Functions  Definations    =====================//

//process operations :: No clear implementation yet
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

void clearResources(); // for clearing on exit



//================ Functions Implementations ===============//



void recvProcess(){
    ProcessParameters recPrc;
    PCB* prc;
    
    while(msgQueueRcvPrc(&recPrc) != -1){
        //allocating memory for prc
        prc = (PCB*) malloc(sizeof(PCB));

        //extrating PCB obj parameters from the recieved object
        prc->id = recPrc->id;
        prc->arrivalTime =  recPrc.arrival_time;
        prc->priority = recPrc.priority;
        prc->executionTime = recvProcess.execution_time;
        prc->remainingTime = recvProcess.execution_time;
        prc->startTime = -1;


        //enqueue to the PCB queue

    }
}

void runPHPF(){

}


void runSRTN(){

}

void runSJF(){
    
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

