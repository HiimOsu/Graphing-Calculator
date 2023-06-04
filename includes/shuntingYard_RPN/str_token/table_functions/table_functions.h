#ifndef TABLE_FUNCTIONS_H
#define TABLE_FUNCTIONS_H

#include <iostream>
#include <cassert>
#include <iomanip>

using namespace std;
const int MAX_ROW = 100;
const int MAX_COL = 256;

//PreConditon: num_state <= MAX_ROW, num_input <= MAX_COL
//PostCondition: init first col to be 0, others to be -1
void init_table(int table[][MAX_COL], int num_state, int num_input);

//PreCondition: State smaller than MAX_ROW
//PostCondition: mark the state as Success(1)
void mark_success(int table[][MAX_COL],int state);

//PreCondition: State smaller than MAX_ROW
//PostCondition: mark the state as Fail(0)
void mark_fail(int table[][MAX_COL],int state);

//PreCondition: state is smaller than MAX_ROW, input and des is smaller than MAX_COL
//PostCondition: Mark the destination for the state in "state" receiving "input".
//table[state][input] = des;
void mark_des(int table[][MAX_COL], int state, int input, int des);

//PreCondition: state is smaller than MAX_ROW, input and des is smaller than MAX_COL
//PostCondition: Return the destination for in "state" receiving "input".
int get_des(const int table[][MAX_COL], int state, int input);

//PreCondition: state is smaller than MAX_ROW, input and des is smaller than MAX_COL
//PostCondition: Return success or fail depending on the corresponding state of that state
//Default value of state = FAIL;
bool get_suc_fail(const int table[][MAX_COL], int state);


//PreConditon: table is init && state is row than MAX_ROW,col is smaller than MAX_COL
//PostCondition: print the table with cout in seperate line.
void print_table(int table[][MAX_COL], int row, int col);

#endif