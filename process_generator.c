#include "headers.h"
#include "process_generator.h"

void clearResources(int);

int main(int argc, char * argv[])
{
    signal(SIGINT, clearResources);
    // TODO Initialization
    // 1. Read the input files. ===>done
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any. ===>done
    // 3. Initiate and create the scheduler and clock processes.                                 ===>done
    // 4. Use this function after creating the clock process to initialize clock                 ===>done
    readInputFile(); // Default Name: processes.txt
    getUserAlgo();


    initMsgQueue();
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
    
    destroyMsgQueue();
    destroyClk(true);
}

void clearResources(int signum)
{
    destroyMsgQueue();
    destroyClk(true);
    exit(0);
}
