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

void heapify_SRTN(int index)
{
    int least = index, left = 2 * index, right = left + 1;

    if((left <= qSize) && (prQueue[left]->remaining_time < prQueue[least]->remaining_time))
		least = left;
	
	if((right <= qSize) && (prQueue[right]->remaining_time < prQueue[least]->remaining_time))
		least = right;

	if(least == index)
		return;
    
	swap_PCB_of_index(least, index);
	heapify_SRTN(least);
}
void heapify_SJF(int index)
{
    
}
void heapify_PHPF(int index)
{

}

void swap_PCB_of_index(int i, int j)
{
    PCB* tmp = prQueue[i];
    prQueue[i] = prQueue[j];
    prQueue[j] = tmp;
}