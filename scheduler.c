#include "headers.h"
#include "scheduler.h"



int main(int argc, char * argv[])
{
    
    //defined user signal 1 for handling the arrival of new process from process_generator
    signal(SIGUSR1, handleProcessArrival);
    //defined user signal 2 for handling finishing signal comming from the process.c
    signal(SIGUSR2, handleProcessFinished);



    algo = atoi(argv[1]);
    processesCount = atoi(argv[2]);


    initClk();
    initMsgQueue();
    InitiateLogger();
    
    
    while(true) {
        printf("Finished Processes: %d\n", finished_process_qSize);
        printf("Processes Count: %d\n", processesCount);
        if (finished_process_qSize == processesCount) {
            LogPerfCalculations();
            break;
        } else {
            pause();
        }
    }

    destroyClk(true);
}
