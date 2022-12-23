#include "headers.h"
#include "scheduler.h"

// Process Arrival
void handle_process_arrival(int signum) {
    printf("Process Arrived!");
}

int main(int argc, char * argv[])
{
    // User-defined signals
    signal(SIGUSR1, handle_process_arrival);

    algo = atoi(argv[1]);
    processesCount = atoi(argv[2]);


    initClk();
    initMsgQueue();

    printf("Algorithm: %d\n", algo);
    printf("Processes Count: %d\n", processesCount);
    //TODO implement the scheduler :)
    //upon termination release the clock resources
    
    while(true){
        pause();
    }

    destroyClk(true);
}
