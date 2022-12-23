#include "../headers.h"


Node *front = NULL, *rear = NULL;
PCB** prQueue; 
int qSize = 0;
void enqueue(PCB* data);
PCB* dequeue();
PCB* peak();
void heapify_SRTN(int index);
void heapify_SJF(int index);
void heapify_PHPF(int index);



