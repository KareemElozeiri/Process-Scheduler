#include "headers.h"
#include "scheduler.h"



int main(int argc, char * argv[])
{
    
    signal(SIGUSR1, handleProcessArrival);



    algo = atoi(argv[1]);
    processesCount = atoi(argv[2]);


    initClk();
    initMsgQueue();

    printf("Algorithm: %d\n", algo);
    printf("Processes Count: %d\n", processesCount);
    
    
    while(true){
        pause();
    }

    destroyClk(true);
}
