/* @Author
Student Name: <Ahmet Kemal Yetkin>
Student ID : <504201506>
Date: <09.01.2020> */


#include "data_structs.h"

void Stack::init(){
    head = NULL;
}

void Stack::push(Subtask* in){
    Subtask *nn=new Subtask;
    nn->name = in->name;
    nn->duration = in->duration;
    nn->next = NULL;

    if (head==NULL) // there is no node in stack
        head=nn;
    else  
    {
        nn->next=head;
        head=nn;
    }   
}

void Stack::pop(){
    if(head->next != NULL){
        Subtask *tmp=head;
        head=head->next; 
        delete tmp;
    }
}

void Stack::close(){
    while (head)
    {
        pop();
    }
}

bool Stack::isEmpty(){
    return head==NULL?true:false;
}


void Queue::init()
{
    front = NULL;
    back = NULL;
}

Process* Queue::dequeue()
{
    Process *topnode;
    topnode = front;
    front=front->next;

    Process* retdata = topnode;
    delete topnode;
    return retdata;
}

void Queue::close()
{
    Process *del;
    while (front)
    {
        del = front;
        front = front ->next;
        delete del;
    }    
}

bool Queue::isEmpty()
{
    return front==NULL;
}

void Queue::enqueue(Process* in)
{
    Process *newprocess = new Process;
    newprocess->name = in->name;
    newprocess->arrival_time = in->arrival_time;
    newprocess->deadline = in->deadline;
    newprocess->task_count = in->task_count;
    newprocess->priority = in->priority;
    newprocess->process_time = in->process_time;
    newprocess->task_stack = in->task_stack;
    newprocess->execution_time = in->execution_time;
    newprocess->actual_a_time = in->actual_a_time;
    newprocess->flag = in->flag;
    newprocess->next = NULL;
    if (isEmpty())
        front = back = newprocess;
    else
    {
        back->next = newprocess;
        back = newprocess;
    }    
}