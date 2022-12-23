#include "headers.h"
#include "scheduler.h"


int main(int argc, char * argv[])
{
    


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
