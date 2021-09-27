/*
PLEASE DO NOT REMOVE ANY FUNCTION OR VARIABLE IN THE STRUCT, IF YOU NEED YOU CAN ADD NEW ONES 
*/
/* @Author
Student Name: <Ahmet Kemal Yetkin>
Student ID : <504201506>
Date: <10.11.2020> */

#ifndef _H
#define _H
#include <stdio.h>

#define ARRAY_SIZE 100

#include "token.h"

struct Counter{
	int token_count=0;
	Token token_array[ARRAY_SIZE];
	Token clone_array[ARRAY_SIZE];
	void read_and_count();
	bool contains(char *,char);
	int findindex(Token [],char[]);
	Token *get_most_common_three();
};
#endif
