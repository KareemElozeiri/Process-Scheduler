#include <stdio.h>
#include <stdlib.h>

// process log data
struct logData {
    int time;
    int id;
    char state[10];
    int arrivaltime;
    int total;
    int remaining;
    int wait;
    int turnaround;
    double weightedturnaround;
};

// performance data
struct perfData {
    double cpu_utilization;
    double avg_weighted_turnaround;
    double avg_waiting_time;
    double std_weighted_turnaround;
};

// process attributes
// to be moved from here later
struct process{
    int id;
    int arrivaltime;
    int priority;
    int runningtime;
};


// round to 2 decimal places
double approx(double x){
    return (int)(x * 100 + .5) / 100.0;
}

// save process data to file
void savelog(int no, struct logData lData[]){
    // open file
    FILE * pFile;
    pFile = fopen("output/scheduler.log", "w");

    // write to file
    fprintf(pFile, "#At time x process y state arr w total z remain y wait k\n");

    for (int i = 0 ; i < no ; i++)
    {
        fprintf(pFile, "#At time %d process %d %s arr %d total %d remain %d wait %d", lData[i].time, lData[i].id, lData[i].state, lData[i].arrivaltime, lData[i].total, lData[i].remaining, lData[i].wait);
        
        // if process is finished print turnaround and weighted turnaround
        if(lData[i].turnaround > 0){

            // approximate to 2 decimal places
            double weightedturnaround = approx(lData[i].weightedturnaround);

            fprintf(pFile, " TA %d  WTA %.2f", lData[i].turnaround, lData[i].weightedturnaround);
        }

        fprintf(pFile, "\n");
    }

    // close file
    fclose(pFile);
}

// save performance data to file
void saveperf(struct perfData pData){
    // open file
    FILE * pFile;
    pFile = fopen("output/scheduler.perf", "w");

    // approximate to 2 decimal places
    pData.cpu_utilization = approx(pData.cpu_utilization);
    pData.avg_weighted_turnaround = approx(pData.avg_weighted_turnaround);
    pData.avg_waiting_time = approx(pData.avg_waiting_time);
    pData.std_weighted_turnaround = approx(pData.std_weighted_turnaround);

    // write to file
    fprintf(pFile, "CPU utilization = %.2f%%\n", pData.cpu_utilization);
    fprintf(pFile, "Avg WTA = %.2f\n", pData.avg_weighted_turnaround);
    fprintf(pFile, "Avg waiting = %.2f\n", pData.avg_waiting_time);
    fprintf(pFile, "Std WTA = %.2f\n", pData.std_weighted_turnaround);

    // close file
    fclose(pFile);
}

// load process data from file
void loadprocesses(struct process processes[]){
    // open file
    FILE * pFile;
    pFile = fopen("processes.txt", "r");

    // read file line by line
    char line[100];
    int i = 0;
    while(fgets(line, sizeof(line), pFile)){
        // ignore lines starting with #
        if(line[0] == '#'){
            continue;
        }

        // read data
        sscanf(line, "%d %d %d %d", &processes[i].id, &processes[i].arrivaltime, &processes[i].runningtime, &processes[i].priority);
        i++;
    }

    // close file
    fclose(pFile);
}

int main(){
    // test savelog
    struct logData lData[3];
    lData[0] = (struct logData){1, 1, "started", 1, 1, 1, 1, 1.9, 1.996};
    lData[1] = (struct logData){2, 2, "started", 2, 2, 2, 2};
    lData[2] = (struct logData){3, 3, "started", 3, 3, 3, 3};
    savelog(3, lData);

    // test saveperf
    struct perfData pData = (struct perfData){1, 2, 3, 4};
    saveperf(pData);

    // test loadprocesses
    struct process processes[100];
    loadprocesses(processes);
}