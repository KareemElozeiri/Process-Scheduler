#include "PCBQueue.h"
#include "../scheduler.h"
void enqueue(PCB* data)
{
    if(algo == PHPF)
    {
        
    }

    prQueue[++qSize] = data; 
    if(qSize == 1)
        return;
    if(algo == SRTN)
    {
        for(int i = qSize/2; i > 0; i--)
            _heapifySRTN(i); 
    }
    else if(algo == SJF)
    {
        
    }
}

PCB* dequeue()
{
    if(algo == PHPF)
    {
        
    }

    if(qSize == 0)
        return NULL;
    PCB* prcs = prQueue[1];
    prQueue[1] = prQueue[qSize--];

    if(qSize > 1)
    {
        if(algo == SRTN)
        {
            _heapifySRTN(1);
        }
        else if(algo == SJF)
        {
            
        }
    }
    return prcs;

}
PCB* peak()
{
    if(qSize == 0)
        return NULL;
    return prQueue[1];
}

void _heapifySRTN(int index)
{

}
void _heapifySJF(int index)
{
    
}