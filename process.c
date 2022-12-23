#include "headers.h"

/* Modify this file as needed*/
int remainingtime;

int main(int agrc, char * argv[])
{
    initClk();


    remainingtime = atoi(argv[1]);
    int schedulerPid = atoi(argv[2]);
    int schedulerClk = atoi(argv[3]);
    printf("Process Started with remining time %d\n || Process PID: %d\n", remainingtime, getpid());

    if(remainingtime>0 && getClk()!=schedulerClk){
        remainingtime--;
    }

    int startTime = getClk();
    int finishTime = getClk()+remainingtime;

    while (getClk()!=finishTime)
    {
        
    }
    


    kill(schedulerPid, SIGUSR2);

    destroyClk(false);
    
    return 0;
}
