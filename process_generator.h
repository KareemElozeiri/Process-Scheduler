#include "headers.h"

#define INPUT_FILE_NAME "processes.txt"

AlgorithmType algo = SJF;
int processesCount = 0;

// ================== Forks PIDs ================== //
pid_t scheduler_pid, clock_pid;

// ================== Processes Queue ================== //
typedef struct ProcessNode
{
    ProcessParameters *data;
    struct ProcessNode *next;
} ProcessNode;
ProcessNode *process_front = NULL, *rear = NULL;
int qSize = 0;  //would equal total number of processes when the program exits
void pop();     //throws front and frees memory
void enqueue(ProcessParameters *val);

void process_enqueue(ProcessParameters *val)
{
    qSize++;
    ProcessNode *newNode = malloc(sizeof(ProcessNode));
    newNode->next = NULL;
    newNode->data = val;
    
    //First node to be added
    if(process_front == NULL && rear == NULL)
    {
        //make both front and rear points to newNode
        process_front = newNode;
        rear = newNode;
    }
    else //not the first
    {
        //add newNode in rear->next
        rear->next = newNode;

        //make newNode as the rear Node
        rear = newNode;
    }
}

void process_pop()
{
    if(process_front == NULL)
        return;
    if(process_front == rear)
        rear = NULL;
    ProcessNode* temp = process_front;
    process_front = process_front->next;
    free(temp->data);   //First free data
    free(temp);
}

//==================functions definations====================//

void getUserAlgo();

void startClk();
void startScheduler();


//=================functions implementation=================//

void readInputFile() {
    FILE* input_file;

    input_file = fopen(INPUT_FILE_NAME, "r");

    if (!input_file) {
        perror("Error: Can't load the input file!");
        exit(EXIT_FAILURE);
    }
    // Variables to hold the file data
    char line[500];
    // Skip the headings line
    fgets(line, sizeof(line), input_file);
    ProcessParameters* prc;
    // Read the processes data
    while (fgets(line, sizeof(line), input_file)) {
        prc = (ProcessParameters*) malloc(sizeof(ProcessParameters));
        sscanf(line, "%d %d %d %d", &(prc->process_id), &(prc->arrival_time), &(prc->execution_time), &(prc->priority));
        process_enqueue(prc);
        processesCount++;
    }
    printf("[+]: Input file read successfully!\n");
    fclose(input_file);
}


void getUserAlgo(){

    int userInput;
    printf("Available Scheduling Algorithms:\n\
            [1] Preemptive Highest Priority First (PHPF)\n\
            [2] Shortest Remaining time Next (SRTN)\n\
            [3] Short Job First (SJF)\n");
    printf("Enter Algorithm No.: ");
    scanf("%d", &userInput);
    if(userInput<1 || userInput>3){
        perror("Invalid Algorithm Number\n");
        exit(FAILURE_CODE);
    }

    algo = userInput-1;
}


void startClk(){
    clock_pid = fork();

    if (clock_pid == -1) {
        perror("Error while forking to start the clk");
        exit(FAILURE_CODE);
    }
    else if (clock_pid == 0) {
        char *const paramList[] = {"./clk.out", NULL};
        execv("./clk.out", paramList);
        exit(FAILURE_CODE);
    }
}

void startScheduler(){
    scheduler_pid = fork();

    if (scheduler_pid == -1) {
        perror("Error while forking to start the scheduler");
        exit(FAILURE_CODE);
    }
    else if (scheduler_pid == 0) {

        char stringAlgo[5];
        char stringProcessesCount[10];

        sprintf(stringAlgo, "%d", algo);
        sprintf(stringProcessesCount, "%d", processesCount);
        char *const paramList[] = {"./scheduler.out", stringAlgo, stringProcessesCount, NULL};


        execv("./scheduler.out", paramList);
        

        exit(FAILURE_CODE);
    }

}