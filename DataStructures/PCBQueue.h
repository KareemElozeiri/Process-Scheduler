#include "../headers.h"


algo = 2; //for testing
Node* newNode(PCB* d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}




Node *front = NULL,
 *rear = NULL;

Node* prQueue; 
int qSize = 0;
void enqueue(Node* data);
Node* dequeue();
Node* peak();


void enqueue(Node *data)
{
    Node *new = newNode(data->data, data->priority);
    if (qSize == 0)
    {
        prQueue->data = new->data;
        prQueue->next = NULL;
        return;
    }
    else if (algo == SJF)
    {
        if (qSize == 1)
        {
            prQueue->next = new;
            return;
        }
        else
        {
            Node *temp = prQueue;
            while (temp->next->data->execution_time < new->data->execution_time)
            {
                temp = temp->next;
            }
            new->next = temp->next;
            temp->next = new;
        }
    }

    if (algo == SRTN)
    {

    }
    else if (algo == PHPF)
    {
    }
}

// Node *dequeue()
// {
//     if (algo == PHPF)
//     {
//     }

//     if (qSize == 0)
//         return NULL;
//     prQueue[1] = prQueue[qSize--];

//     if (qSize > 1)
//     {
//         if (algo == SRTN)
//         {
//             _heapifySRTN(1);
//         }
//         else if (algo == SJF)
//         {
//         }
//     }
//     return prcs;
// }

Node *peak()
{
    if (qSize == 0)
        return NULL;
    return prQueue;
}


