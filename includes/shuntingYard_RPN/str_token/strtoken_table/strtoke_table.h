#ifndef STRTOKEN_TABLE_H
#define STRTOKEN_TABLE_H

#include "../table_functions/table_functions.h"

    int     input(char c);
    void    makeTable(int table[][MAX_COL], const int NUM_STATE,const int NUM_INPUT);

    void    go_next_pos(const string& _str, string::iterator& _pos);
    int     get_next_state(int table[][MAX_COL],const string& _str, const string::iterator& _pos, int current_state);
    
    
#endif