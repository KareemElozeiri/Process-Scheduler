#include "headers.h"

//============== Data structures ==========//

// TODO implement queue for PCBs

AlgorithmType algo;


//============ Functions  Definations    =====================//

//process operations :: No clear implementation yet
int forkNewProcess();
void startProcess();
void stopProcess();


//communication with process_generator
void recvProcess();
void getAlgoType(); // gets algo type from process generator



// TODO: How to communicate the process with its remaining time?

//-------------- Scheduling Algorithms ------------//
void runPHPF();
void runSRTN();
void runSJF();
//------------------------------------------------//

void runAlgo(AlgorithmType algo); // runs choosen algo by the user in process generator

void clearResources(); // for clearing on exit



//================ Functions Implementations ===============//

