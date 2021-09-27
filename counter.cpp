/*
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
/* @Author
Student Name: <Ahmet Kemal Yetkin>
Student ID : <504201506>
Date: <10.11.2020> */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "counter.h"

using namespace std;

	
int Counter::findindex(Token *arr,char elem[]){
    // it compares the two characters and returning value in according to returned value of contains function
	for(int i = 0; i < token_count; i++){
        if(contains(&token_array[i].token[0], elem[0]) && contains(&token_array[i].token[1], elem[1])){
            return i;
        }
    }
    return -1;
} 

bool Counter::contains(char *token, char target){
    // it compares the two characters and returning value accordingly
	if(*token == target){
        return true;
    }
    else{
        return false;
    }
}

void Counter::read_and_count(){
    //Reading the 'pi_approximate' file with fstream and checking the '.' 
    fstream f("pi_approximate", fstream::in );
    string pi_approximate;
    string s;
    getline( f, s, '\0');
    f.close();
	for(int i = 0; i < (int) s.length()-1; i++) {
        if (contains(&s[i],'.') || contains(&s[i],',')) {
            pi_approximate.clear();
            continue;
        }
        pi_approximate += s[i];
    }
    //Counting the tokens number and putting them into token_array
    for(int i = 0; i < (int) pi_approximate.length() - 1; i++){
        bool count_increased = false;
        char a = pi_approximate[i]; //i=0 a=1, i=1 a=4, i=2 a=1, i=3 a=5, i=4 a=4
        char b = pi_approximate[i+1];// i=1 b=4 i=2 b=1, i=3 b=5, i=4 b=4, i=5 b=1
        
        for(int p = 0; p < token_count; p++){
            if(token_array[p].token[0] == a && token_array[p].token[1] == b){
                token_array[p].count++;
                count_increased = true;
            }
        }
        if(count_increased==false){
            token_array[token_count].count = 1;
            token_array[token_count].token[0] = a;
            token_array[token_count].token[1] = b;
            token_count++; // token_count = 1, 2, 3, 4
        }
    }
}


Token *Counter::get_most_common_three(){
    //token_array coppying as a clone_array. All tokens which include in token_array, are putting into clone_array
    for(int x=0; x < token_count - 1; x++){
        clone_array[x] = token_array[x];
    }
	for(int i=0; i < token_count - 1; i++){
        bool already_increased = false;

        if(clone_array[0].count < token_array[i].count){
            clone_array[0].count = token_array[i].count;
            clone_array[0].token[0] = token_array[i].token[0];
            clone_array[0].token[1] = token_array[i].token[1];
            already_increased = true;
            }
        if(clone_array[1].count < token_array[i].count && !already_increased){
            clone_array[1].count = token_array[i].count;
            clone_array[1].token[0] = token_array[i].token[0];
            clone_array[1].token[1] = token_array[i].token[1];
            already_increased = true;
        }
        if(clone_array[2].count < token_array[i].count && !already_increased){
            clone_array[2].count = token_array[i].count;
            clone_array[2].token[0] = token_array[i].token[0];
            clone_array[2].token[1] = token_array[i].token[1];
            already_increased = true;
        }
    }
    return clone_array;
}
