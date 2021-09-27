#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct Resistor_Record{
    char group;
    double value;
    int quantity;
    int differ = 0;
    Resistor_Record *next;
};

struct Circuit{
    Resistor_Record *head;
    Resistor_Record *head2;
    FILE* inputfile;
    bool quantity_flag=false;
    void create(const char *filename);
    void add_resistor(char group, double value);
    void remove_resistor(double value);
    void delete_resistor(Resistor_Record *nrptr);
    void circuit_info();
    void clear();
    void print_list();

};


void Circuit::create(const char *filename){
    head = NULL;
    head2 = NULL;
    ifstream file( filename, ios::in );
    char group;
    double value;
    bool prev_value = false;
    while(file.peek() != EOF){
        file >> group >> value;
        
        if (value==0  && !prev_value){
            print_list();
            circuit_info();
            prev_value = true;
        }
        else if ( value <  0){
            prev_value = false;
            remove_resistor(value); 
            }

        else {
            prev_value = false;
            add_resistor(group,value);
            }
        value = 1;
    }

    file.close();
}
	

void Circuit::add_resistor(char group, double value){
    Resistor_Record *node = new Resistor_Record;
    node->group = group;
    node->value = value;
    node->quantity = 1;
    node->next = NULL;
    Resistor_Record *traverse, *tail;

    traverse = head;
    if(value != 0){

        if(!traverse){
        head = node;
        }
        else{
            int i = 0;
            while(traverse && traverse->value < node->value){
                tail = traverse;
                traverse = traverse->next;
                i++;
            }
            if(i==0) // new node is placed instead of head
            {
                node->next=head;
                head=node;
            }

            else if(traverse) // add into the mid position
            {
                if(traverse && tail->next->value == node->value){
                    traverse->quantity++;
                    
                    if( tail->next->group != node->group){
                    traverse->differ++;
                    }
                }
                else {
                    node->next=traverse; 
                    tail->next=node;
                }
            }
            else // add to the end of the list
            {
                tail->next=node;  
            }
        }
    }


    Resistor_Record *node2 = new Resistor_Record;
    node2->group = group;
    node2->value = value;
    node2->quantity = 1;
    node2->next = NULL;
    Resistor_Record *traverse2, *tail2;

    traverse2 = head2;
    if(value != 0){

        if(!traverse2){
        head2 = node2;
        return;
        }

        int i = 0;
        while(traverse2 && traverse2->group < node2->group){
            tail2 = traverse2;
            traverse2 = traverse2->next;
            i++;
        }
        if(i==0) // new node is placed instead of head
        {
            node2->next=head2;
            head2=node2;
        }

        else if(traverse2) // add into the mid position
        {
            if(traverse2 && tail2->next->group == node2->group){
                traverse2->quantity++;
                
                if( tail2->next->group != node2->group){
                traverse2->differ++;
                }
            }
            else {
                node2->next=traverse2; 
                tail2->next=node2;
            }
        }
        else // add to the end of the list
        {
            tail2->next=node2;  
        }
    }
}


void Circuit::remove_resistor(double value){
    Resistor_Record *traverse;
    traverse = head;
    bool found = false;
    while(traverse){
        if(traverse->value == -value){
            traverse->quantity--;
            found = true;
            if (traverse->quantity == 0){
                delete_resistor(traverse);
                return;
            }
        }
        traverse = traverse->next;
    }
    if (!found) {
        quantity_flag = true;
        return;
    }
}



void Circuit::delete_resistor(Resistor_Record *nrptr){
    Resistor_Record *traverse=head;
    if(nrptr->group == head->group){
        head = head->next;
    }
    else if (nrptr->quantity == 0){
        while(traverse->next->value != nrptr->value){
            
            traverse = traverse->next;
        }
        traverse->next=nrptr->next;
    }   
    return;

}

void Circuit::clear(){
    Resistor_Record *dust, *dust2;

    while(head){
        dust = head;
        head = head->next;
        delete[] dust;
    }
    while(head2){
        dust2 = head2;
        head2 = head2->next;
        delete[] dust2;
    }

    delete[] head;
    delete[] head2;

}

void Circuit::circuit_info(){
    Resistor_Record *traverse=head;
    double total=0;
    double result=0;
    while(traverse){
        if(traverse->differ > 0){
            total = traverse->quantity * traverse->value;
            result += total;
        }
        else if(traverse->quantity > 1){
            total = traverse->value/traverse->quantity;
            result += total;
        }
        else if(traverse->quantity==1){ 
        result += traverse->value;
        }

        traverse = traverse->next;
    }
    cout << "Total resistance=" << result << " ohm";
    cout << endl;
}



void Circuit::print_list()
{
	Resistor_Record *traverse = head;

    if(quantity_flag==true) cout << "NO_RESISTOR" << endl;
	for (int i=1;traverse;i++,traverse=traverse->next){
	    cout<<traverse->value << ":" << traverse->quantity <<endl;
    }
}

int main(int argc, char** argv) {

    Circuit circuitlist;
    circuitlist.create(argv[1]);

    circuitlist.clear();
    return 0;
}



