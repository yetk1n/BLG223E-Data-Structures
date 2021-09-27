/* @Author
Student Name: <Ahmet Kemal Yetkin>
Student ID : <504201506>
Date: <09.01.2020> */

#include <string>
using namespace std;

struct Subtask{
char name;
int duration;
Subtask* next;
};


struct Stack{
Subtask* head;
void create(const char *filename);
void init();
void close();
void push(Subtask* in);
void pop();
bool isEmpty();
};


struct Process{
string name;
int arrival_time;
int deadline=0;
int task_count;
int priority;
int process_time=0;
int execution_time=0;
bool flag = false;
int actual_a_time = 0;
Stack task_stack;
Process* next;
};


struct Queue{
Process* front;
Process* back;
void init();
void close();
void enqueue(Process* in);
Process* dequeue();
bool isEmpty();
void print_list(Process* in);
};



struct MultiQueue{
Queue queues[3];
void init();
void close();
void enqueue(Process* in);
Process* dequeue(int priority);
bool isEmpty();
Process* front(int priority);
};