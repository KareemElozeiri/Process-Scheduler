#include "headers.h"

/* Modify this file as needed*/
int remainingtime;

int main(int agrc, char * argv[])
{
    initClk();


    remainingtime = atoi(argv[1]);
    int schedulerPid = atoi(argv[2]);
    int schedulerClk = atoi(argv[3]);

    if(remainingtime>0 && getClk()!=schedulerClk){
        remainingtime--;
    }

    while (remainingtime > 0)
    {
        remainingtime--;
    }
    


    kill(schedulerPid, SIGUSR2);

    destroyClk(false);
    
    return 0;
}
