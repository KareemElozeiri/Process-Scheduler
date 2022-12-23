#include "../headers.h"


Node *front = NULL, *rear = NULL;
PCB** prQueue; 
int qSize = 0;
void enqueue(PCB* data);
PCB* dequeue();
PCB* peak();
void _heapifySRTN(int index);
void _heapifySJF(int index);



