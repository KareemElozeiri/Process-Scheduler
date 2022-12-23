#include "../headers.h"


int algo = 2; //for testing
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
void dequeue();
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
        //this doesn't check the head as it is non-premative
        Node *temp = prQueue;
        int newTime = new->data->execution_time;

        while ((temp->next != NULL) && (temp->next->data->execution_time < newTime))
        {
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
    }

    if (algo == SRTN)
    {
        Node *temp = prQueue;
        int newTime = new->data->remaining_time;

        if(prQueue->data->remaining_time > newTime)
        {
            new->next = prQueue;
            prQueue = new;
        }
        else
        {
            while ((temp->next != NULL) && (temp->next->data->remaining_time < newTime))
            {
                temp = temp->next;
            }
            new->next = temp->next;
            temp->next = new;
        }
    }
    else if (algo == PHPF)
    {//Preemptive Highest Priority First
        Node *temp = prQueue;
        int newPri = new->priority;

        if(prQueue->priority < newPri)
        {
            new->next = prQueue;
            prQueue = new;
        }
        else
        {
            while ((temp->next != NULL) && (temp->next->data->remaining_time > newPri))
            {
                temp = temp->next;
            }
            new->next = temp->next;
            temp->next = new;
        }
    }
}

void dequeue()
{
    Node* temp = prQueue;
    prQueue = temp->next;
    free(temp);
}

Node *peak()
{
    if (qSize == 0)
        return NULL;
    return prQueue;
}


