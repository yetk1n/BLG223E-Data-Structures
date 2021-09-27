/* @Author
Student Name: <Ahmet Kemal Yetkin>
Student ID : <504201506>
Date: <09.01.2020> */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "data_structs.h"
//Priority 1 always gets the access to CPU
// if SC is deactive: Priority 2 > Priority 3
// special condition: start ----> 2 ----->2 |now sc active|----> 3 |now sc deactive|
//                          ----->2 ----->2 |now sc active| if there is no 3 |now sc deactive|

using namespace std;


void Stack::create(const char *filename){
    ifstream file(filename, ios::in);

    init();
    Queue queue;
    queue.init();
    Process* pinput = new Process;
    Subtask* first = new Subtask;

    while(file.peek() != EOF){
        
        file >> pinput->name >> pinput->priority;
        file >> pinput->arrival_time >> pinput->task_count;
        if (file.eof()) break; 
        for(int i = 0; i < pinput->task_count ; i++){
            file >> first->name >> first->duration;
            pinput->execution_time += first->duration;
            push(first);
        }
        pinput->task_stack.head = head;
        queue.enqueue(pinput);
        pinput->execution_time = 0;
        head = NULL;  
    }
    file.close();


    MultiQueue *multiqueue = new MultiQueue;
    multiqueue->queues[0].init();
    multiqueue->queues[1].init();
    multiqueue->queues[2].init();

    while(queue.front){
        if(queue.front->priority == 1){
            multiqueue->queues[0].enqueue(queue.front);
        }
        if(queue.front->priority == 2){
            multiqueue->queues[1].enqueue(queue.front);
        }
        if(queue.front->priority == 3){
            multiqueue->queues[2].enqueue(queue.front);
        }
        queue.front = queue.front->next;
    };
    bool special_condition = false;
    int sc_count = 0;
    int subtask_duration = 0;
    for(int i = 0; i < 3; i++){
        //birinci indeks için
        if(multiqueue->queues[i].front && multiqueue->queues[i].front->arrival_time==0){
            cout << multiqueue->queues[i].front->name <<  " " << multiqueue->queues[i].front->task_stack.head->name << endl;
            subtask_duration = multiqueue->queues[i].front->task_stack.head->duration;

            if(multiqueue->queues[i].front->priority == 2){
                sc_count += 1;
            }
            if(multiqueue->queues[i].front->task_stack.head->next){
                multiqueue->queues[i].front->process_time += multiqueue->queues[i].front->task_stack.head->duration;
                multiqueue->queues[i].front->task_stack.head = multiqueue->queues[i].front->task_stack.head->next;
                multiqueue->queues[i].front->flag = true;
            }
            else 
                multiqueue->queues[i].dequeue();
        }
    }

    int lateness = 0;
    int cumulative_lateness = 0;
    int subtask_checking_time = 0;
    //system_time-arrival_time + execution_time-process_time
    while(true){
        subtask_checking_time = subtask_duration;

        while(multiqueue->queues[0].front && multiqueue->queues[0].front->arrival_time <= subtask_duration){
            //priority 1 ler için
            if(multiqueue->queues[0].front && multiqueue->queues[0].front->arrival_time <= subtask_duration){
                cout << multiqueue->queues[0].front->name <<  " " << multiqueue->queues[0].front->task_stack.head->name << endl;
                subtask_duration += multiqueue->queues[0].front->task_stack.head->duration;
                multiqueue->queues[0].front->process_time += multiqueue->queues[0].front->task_stack.head->duration;
                //check the priority 2 is still in the process
                if(multiqueue->queues[1].front && multiqueue->queues[1].front->flag)
                    multiqueue->queues[1].front->process_time += multiqueue->queues[0].front->task_stack.head->duration;
                //check the priority 3 is still in the process
                if(multiqueue->queues[2].front && multiqueue->queues[2].front->flag)
                    multiqueue->queues[2].front->process_time += multiqueue->queues[0].front->task_stack.head->duration;
                
                if(!multiqueue->queues[0].front->flag)
                    multiqueue->queues[0].front->actual_a_time = subtask_duration - multiqueue->queues[0].front->task_stack.head->duration;
                

                if(multiqueue->queues[0].front->task_stack.head->next){
                    multiqueue->queues[0].front->task_stack.head = multiqueue->queues[0].front->task_stack.head->next;
                    multiqueue->queues[0].front->flag = true;
                }
                else {
                    if(!multiqueue->queues[0].front->flag)
                        multiqueue->queues[0].front->process_time = multiqueue->queues[0].front->execution_time;
                    lateness = multiqueue->queues[0].front->actual_a_time - multiqueue->queues[0].front->arrival_time + multiqueue->queues[0].front->process_time - multiqueue->queues[0].front->execution_time ;
                    cumulative_lateness += lateness;
                    multiqueue->queues[0].dequeue();
                }
            }
        }

        while(multiqueue->queues[2].front && multiqueue->queues[2].front->arrival_time <= subtask_duration){
            if(multiqueue->queues[1].front && multiqueue->queues[1].front->arrival_time > subtask_duration) special_condition = true;
            if(multiqueue->queues[0].front && multiqueue->queues[0].front->arrival_time > subtask_duration) special_condition = true;
            //priority 3
            while(special_condition || !multiqueue->queues[1].front){

                cout << multiqueue->queues[2].front->name <<  " " << multiqueue->queues[2].front->task_stack.head->name << endl;
                subtask_duration += multiqueue->queues[2].front->task_stack.head->duration;
                multiqueue->queues[2].front->process_time += multiqueue->queues[2].front->task_stack.head->duration;
                //check the priority 1 is still in the process
                if(multiqueue->queues[0].front && multiqueue->queues[0].front->flag)
                    multiqueue->queues[0].front->process_time += multiqueue->queues[2].front->task_stack.head->duration;
                //check the priority 2 is still in the process
                if(multiqueue->queues[1].front && multiqueue->queues[1].front->flag)
                    multiqueue->queues[1].front->process_time += multiqueue->queues[2].front->task_stack.head->duration;

                if(!multiqueue->queues[2].front->flag)
                    multiqueue->queues[2].front->actual_a_time = subtask_duration - multiqueue->queues[2].front->task_stack.head->duration;
                

                if(multiqueue->queues[2].front->task_stack.head->next){
                    multiqueue->queues[2].front->task_stack.head = multiqueue->queues[2].front->task_stack.head->next;
                    multiqueue->queues[2].front->flag = true;
                    special_condition = false;
                    sc_count = 0;
                }
                else {
                    if(!multiqueue->queues[2].front->flag)
                        multiqueue->queues[2].front->process_time = multiqueue->queues[2].front->execution_time;
                    lateness = multiqueue->queues[2].front->actual_a_time - multiqueue->queues[2].front->arrival_time + multiqueue->queues[2].front->process_time - multiqueue->queues[2].front->execution_time ;
                    cumulative_lateness += lateness;
                    multiqueue->queues[2].dequeue();
                }
                special_condition = false;
                sc_count = 0;
                if(!multiqueue->queues[2].front)
                    break;
            }
            break;
        }
        //priority2
        if(multiqueue->queues[1].front && multiqueue->queues[1].front->arrival_time <= subtask_duration ){
            cout << multiqueue->queues[1].front->name <<  " " << multiqueue->queues[1].front->task_stack.head->name << endl;
            subtask_duration += multiqueue->queues[1].front->task_stack.head->duration;
            multiqueue->queues[1].front->process_time += multiqueue->queues[1].front->task_stack.head->duration;
            
            //check the priority 3 is still in the process
            if(multiqueue->queues[2].front && multiqueue->queues[2].front->flag)
                multiqueue->queues[2].front->process_time += multiqueue->queues[1].front->task_stack.head->duration;
            //check the priority 1 is still in the process
            if(multiqueue->queues[0].front && multiqueue->queues[0].front->flag)
                multiqueue->queues[0].front->process_time += multiqueue->queues[1].front->task_stack.head->duration;   

            sc_count += 1;
            if(sc_count % 2 == 0)
                special_condition = true;

            if(!multiqueue->queues[1].front->flag)
                multiqueue->queues[1].front->actual_a_time = subtask_duration - multiqueue->queues[1].front->task_stack.head->duration;
            
            if(multiqueue->queues[1].front->task_stack.head->next){
                multiqueue->queues[1].front->flag = true;
                multiqueue->queues[1].front->task_stack.head = multiqueue->queues[1].front->task_stack.head->next;
            }
            else {
                if(!multiqueue->queues[1].front->flag)
                    multiqueue->queues[1].front->process_time = multiqueue->queues[1].front->execution_time;
                lateness = multiqueue->queues[1].front->actual_a_time - multiqueue->queues[1].front->arrival_time + multiqueue->queues[1].front->process_time - multiqueue->queues[1].front->execution_time ;
                cumulative_lateness += lateness;
                multiqueue->queues[1].dequeue();
            }
        }
        
        if(subtask_duration == subtask_checking_time){
            special_condition = false;
            subtask_duration++;
        }
        if(!multiqueue->queues[0].front && !multiqueue->queues[1].front && !multiqueue->queues[2].front){
            cout << "Cumulative Lateness: " << cumulative_lateness << endl;
            break;
        }
        
    }
}



int main(int argc, char** argv) {
    Stack stack;
    stack.create(argv[1]);
    stack.close();
 
    return 0;
}