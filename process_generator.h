// ADD functions and data structures to be used in the process_generator



//==================functions definations====================//
void startClk();
void startScheduler();


//=================functions implementation=================//
void startClk(){
    pid_t pid = fork();

    if(pid==-1){
        perror("Error while forking to start the clk");
        exit(-1);
    }
    else if(pid==0){
        execv("./clk.out",NULL);
        exit(-1);
    }

}

void startScheduler(){
    pid_t pid = fork();

    if(pid==-1){
        perror("Error while forking to start the scheduler");
        exit(-1);
    }
    else if(pid==0){
        execv("./scheduler.out",NULL);
    }

}