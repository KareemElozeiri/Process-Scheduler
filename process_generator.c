#include "headers.h"
#include "process_generator.h"

void clearResources(int);

int main(int argc, char * argv[])
{
    //clearing resources on interrupt signal
    signal(SIGINT, clearResources);
   
    readInputFile(); // Default Name: processes.txt
    getUserAlgo();

    //initializing message queue
    initMsgQueue();
    //starting scheduler and clock
    startScheduler();
    startClk();

    printf("Scheduler PID: %d\n", scheduler_pid);
    printf("Clock PID: %d\n", clock_pid);

    
    initClk();
    // To get time use this
    int current_time = getClk();
    // TODO Generation Main Loop ===>done
    // 5. Create a data structure for processes and provide it with its parameters. ===>done
    // 6. Send the information to the scheduler at the appropriate time.===>done
    // 7. Clear clock resources
    while(processesCount) {
        current_time = getClk();
        kill(clock_pid, SIGSTOP);
        while(process_front->data->arrival_time == current_time) {
            msgQueueSendPrc(process_front->data);
            // Notify the scheduler that a process arrived
            kill(scheduler_pid, SIGUSR1);
            process_pop();
            processesCount--;
            if (processesCount == 0) break;
        }
        kill(clock_pid, SIGCONT);
    }

    printf("All processes have been sent to the scheduler!\n");
    pause(); // Wait until the scheduler finishes

    clearResources(0);
}

void clearResources(int signum)
{
    destroyMsgQueue();
    destroyClk(true);
    exit(0);
}
