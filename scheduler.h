#pragma once 
#include "headers.h"

AlgorithmType algo;
int processesCount;
PCB* runningProcess = NULL;

// Logging File
FILE* logging_file;
FILE* perf_calculations_file;

// ================== Logger ================== //

void InitiateLogger()
{
    logging_file = fopen("Scheduler.log", "w");
    if (logging_file == NULL)
    {
        perror("Error in Scheduler.log Creation/Opening!");
        exit(EXIT_FAILURE);
    }
    // Log the heading
    fprintf(logging_file, "#At time x process y state arr w total z remain y wait k\n"); 
    fclose(logging_file);
    // Open in append mode
    logging_file = fopen("Scheduler.log", "a");
}

void LogUpdate(PCB* p, LoggerState logger_state)
{
    switch (logger_state)
    {
    case STARTING_PROCESS:
        fprintf(logging_file, "At time %d process %d started arr %d total %d remain %d wait %d\n", p->start_time, p->id, p->arrival_time, p->execution_time, p->remaining_time, p->waiting_time); 
        break;
    case FINISHING_PROCESS:
        fprintf(logging_file, "At time %d process %d finished arr %d total %d remain %d wait %d TA %d WTA %d\n", p->finish_time, p->id, p->arrival_time, p->execution_time, p->remaining_time, p->waiting_time, p->turnaround_time, p->weighted_turnaround_time); 
        break;
    default:
        break;
    }
    fclose(logging_file);
    logging_file = fopen("Scheduler.log", "a");
}


// ================== Finished Processes Queue ================== //
typedef struct FinishedProcessNode
{
    PCB *data;
    struct FinishedProcessNode *next;
} FinishedProcessNode;
FinishedProcessNode *finished_process_front = NULL, *finished_process_rear = NULL;
int finished_process_qSize = 0;  //would equal total number of pcbs when the program exits
void finished_process_enqueue(PCB *val);
void finished_process_pop();     //throws front and frees memory

void finished_process_enqueue(PCB *val)
{
    finished_process_qSize++;
    FinishedProcessNode *newNode = malloc(sizeof(FinishedProcessNode));
    newNode->next = NULL;
    newNode->data = val;
    
    //First node to be added
    if(finished_process_front == NULL && finished_process_rear == NULL)
    {
        //make both front and rear points to newNode
        finished_process_front = newNode;
        finished_process_rear = newNode;
    }
    else //not the first
    {
        //add newNode in rear->next
        finished_process_rear->next = newNode;

        //make newNode as the rear Node
        finished_process_rear = newNode;
    }
}

void finished_process_pop()
{
    if(finished_process_front == NULL)
        return;
    if(finished_process_front == finished_process_rear)
        finished_process_rear = NULL;
    FinishedProcessNode* temp = finished_process_front;
    finished_process_front = finished_process_front->next;
    // free(temp->data);   //First free data
    // free(temp);
}

// ================== PCB Queue ================== //
typedef struct PCBNode
{
    PCB *data;
    struct PCBNode *next;
} PCBNode;
PCBNode *pcb_front = NULL, *pcb_rear = NULL;
int pcb_qSize = 0;  //would equal total number of pcbs when the program exits
void pcb_pop();     //throws front and frees memory
void pcb_enqueue(PCB *val);


//==================Priority queue========//
PCB** prQueue; //shares same functions with Queue
void sortTime(int index);
void sortPriority(int index);
void swap(int ind1, int ind2);

void sortPriority(int index)
{
    int least = index, left = 2 * index, right = left + 1;

    if((left <= pcb_qSize) && (prQueue[left]->priority < prQueue[least]->priority))
		least = left;
	
	if((right <= pcb_qSize) && (prQueue[right]->priority < prQueue[least]->priority))
		least = right;

	if(least == index)
		return;

	swap(least, index);
	sortPriority(least);
}

void sortTime(int index)
{
    int least = index, left = 2 * index, right = left + 1;

    if((left <= pcb_qSize) && (prQueue[left]->remaining_time < prQueue[least]->remaining_time))
		least = left;
	
	if((right <= pcb_qSize) && (prQueue[right]->remaining_time < prQueue[least]->remaining_time))
		least = right;

	if(least == index)
		return;
    
	swap(least, index);
	sortTime(least);
}



void swap(int ind1, int ind2)
{
    PCB* tmp = prQueue[ind1];
    prQueue[ind1] = prQueue[ind2];
    prQueue[ind2] = tmp;
}
//=================implementations=============//


void pcb_enqueue(PCB *val)
{
    pcb_qSize++;
    PCBNode *newNode = malloc(sizeof(PCBNode));
    newNode->next = NULL;
    newNode->data = val;
    
    //First node to be added
    if(pcb_front == NULL && pcb_rear == NULL)
    {
        //make both front and rear points to newNode
        pcb_front = newNode;
        pcb_rear = newNode;
    }
    else //not the first
    {
        if(algo==SJF || algo==SRTN){
            if(newNode->data->remaining_time<pcb_front->data->remaining_time){
                newNode->next = pcb_front;
                pcb_front = newNode;
                return;
            }
            PCBNode* prev = pcb_front;
            PCBNode* next = pcb_front->next;
            while(next!=NULL){
                if(newNode->data->remaining_time<next->data->remaining_time){
                    newNode->next = next;
                    prev->next = newNode;
                    return;
                }
                prev = prev->next;
                next = next->next;
            }

        }
        else{
            if(newNode->data->priority<pcb_front->data->priority){
                newNode->next = pcb_front;
                pcb_front = newNode;
                return;
            }
            PCBNode* prev = pcb_front;
            PCBNode* next = pcb_front->next;
            while(next!=NULL){
                if(newNode->data->priority<next->data->priority){
                    newNode->next = next;
                    prev->next = newNode;
                    return;
                }
                prev = prev->next;
                next = next->next;
            }

        }
        //add newNode in rear->next
        pcb_rear->next = newNode;

        //make newNode as the rear Node
        pcb_rear = newNode;
    }

    // printf("test1\n");
    // int new_index = pcb_qSize+1;
    // prQueue[new_index] = val; //ignoring 0 index by post-increment
    // printf("test1\n");
    // if(pcb_qSize <= 1){
    //     printf("test1\n");
    //     return;
    // }
    
    // printf("test1\n");
    // if(algo == SRTN || algo==SJF){
    //     for(int i = pcb_qSize/2; i > 0; i--){
    //         printf("test\n");
    //         sortTime(i); //heapify from parent
    //     }
    // }
    // else if(algo == PHPF){
    //     for(int i = pcb_qSize/2; i > 0; i--){
    //         printf("test\n");
    //         sortPriority(i);

    //     }
    // }

}

void pcb_pop()
{
    if(pcb_front == NULL)
        return;
    if(pcb_front == pcb_rear)
        pcb_rear = NULL;
    PCBNode* temp = pcb_front;
    pcb_front = pcb_front->next;
  
}

//==================functions definations====================//

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



//hanlder for handling processes arrival and finish
void handleProcessArrival(int signum);
void handleProcessFinish(int signum);

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
        prc->waiting_time = 0;
        printf("Rec Prc ID: %d, arr: %d\n", prc->id, prc->arrival_time);


        //enqueue to the PCB queue
        pcb_enqueue(prc);

    }
}

void runPHPF(){


}


void runSRTN(){

}

void runSJF(){
    if(runningProcess == NULL && pcb_front != NULL) {
        runningProcess = pcb_front->data;
        pcb_pop();
        printf("RUNNING PROCESS: id: %d, arr: %d\n", runningProcess->id, runningProcess->arrival_time);
        runningProcess->process_id = forkNewProcess(runningProcess->remaining_time);
        runningProcess->start_time = getClk();
        LogUpdate(runningProcess, STARTING_PROCESS);
    }
    
}


void runAlgo(){

    printf("Running RunAlgo\n");
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


void FinalizeProcessParameters(PCB* p) {
    p->finish_time = getClk();
    p->waiting_time = p->finish_time - p->arrival_time - p->execution_time;
    p->turnaround_time = p->finish_time - p->arrival_time;
    p->weighted_turnaround_time = p->turnaround_time / (float) p->execution_time;
    p->weighted_turnaround_time = round (p->weighted_turnaround_time * 100) / 100;
    LogUpdate(p, FINISHING_PROCESS);
}

void RegisterFinishedProcess(PCB* p) {
    finished_process_enqueue(p);
}

void handleProcessFinished(int signum){
    printf("Process with PID:%d finished!\n", runningProcess->process_id);
    FinalizeProcessParameters(runningProcess);
    RegisterFinishedProcess(runningProcess);   
    runningProcess = NULL;
    runAlgo();
}



// ================ Perf Calculations ================= //

void CalculatePerf(PerfCalculation* perf) {
    float total_execution_time = 0;
    float total_WTA = 0;
    float total_waiting_time = 0;

    PCB** finished_processes = calloc(processesCount, sizeof(PCB*));
    int counter = 0;

    while (finished_process_front)
    {
        PCB* finished_process = finished_process_front->data;
        total_execution_time += finished_process->execution_time;
        total_WTA += finished_process->weighted_turnaround_time;
        total_waiting_time += finished_process->waiting_time;
        finished_processes[counter] = finished_process;
        finished_process_pop();
        counter++;
    }

    float cpu_util = (1.0 * total_execution_time / (getClk() - 1)) * 100;
    float avg_WTA = total_WTA / processesCount;    
    float avg_waiting_time = total_waiting_time / processesCount;

    perf->cpu_util = cpu_util;
    perf->avg_WTA = avg_WTA;
    perf->avg_waiting_time = avg_waiting_time;
    perf->WTA_std = 0;

    // Calculate STD
    for (int i = 1; i < processesCount; i++) {
        perf->WTA_std += (finished_processes[i]->weighted_turnaround_time - avg_WTA) * (finished_processes[i]->weighted_turnaround_time - avg_WTA);
    }
    perf->WTA_std = perf->WTA_std / processesCount;
}

void LogPerfCalculations()
{
    // Open in append mode
    perf_calculations_file = fopen("Scheduler.perf", "w");
    PerfCalculation* perf_calculations;
    CalculatePerf(perf_calculations);
    fprintf(perf_calculations_file, "CPU utilization =  %.6f%%\n", perf_calculations->cpu_util);
    fprintf(perf_calculations_file, "Avg WTA =  %.6f\n", perf_calculations->avg_WTA);
    fprintf(perf_calculations_file, "Avg Waiting =  %.6f\n", perf_calculations->avg_waiting_time);
    fprintf(perf_calculations_file, "Std WTA =  %.6f\n", perf_calculations->WTA_std);
    fclose(perf_calculations_file);
}