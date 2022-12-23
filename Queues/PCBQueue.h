#include "../headers.h"


Node *front = NULL, *rear = NULL;
PCB** prQueue; //shares same functions with Queue
int qSize = 0;  //current number of elements in queue
void enqueue(PCB* data);
PCB* dequeue();
PCB* peak();
void _heapifySRTN(int index);
void _heapifySJF(int index);



