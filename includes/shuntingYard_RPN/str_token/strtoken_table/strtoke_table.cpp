#include "strtoke_table.h"

int input(char c) {
    const int //State
    _DEFAULT = 0,
    _ALPH    = 1,
    _NUMB    = 2,
    _PUN     = 3,
    _DOT     = 4,
    _INVALID = 5,
    _NULL    = 6;
    if(c == '\0')
        return _NULL;
    switch((int) c){ 
        case 33: case 34: case 39: case 40:
        case 41: case 44: case 63:
        return _PUN;
    }
    
    if(c == '.')
        return _DOT;
    if(c >= 48 && c <= 57)      //ASCII: 0-9 (48 - 57) NUMB
        return _NUMB;
    if(c >= 65 && c <= 90)      //ASCII: A-Z (65 - 90) ALPH
        return _ALPH;
    if(c >= 97 && c <= 122)     //ASCII: a-z (97 - 122) ALPH
        return _ALPH;

    return _INVALID;
}

void makeTable(int table[][MAX_COL], const int NUM_STATE,const int NUM_INPUT){

    const int //State
    _DEFAULT = 0,
    _ALPH    = 1,
    _NUMB    = 2,
    _PUN     = 3,
    _DOT     = 4,
    _INVALID = 5,
    _NULL    = 6;

    init_table(table, NUM_STATE, NUM_INPUT);
    
    //Success state:
    mark_success(table, _ALPH);
    mark_success(table, _NUMB);
    mark_success(table, _PUN);
    mark_success(table, _DOT);

    //Fail state:
    mark_fail(table, _INVALID);

    //Default
    mark_des(table, _DEFAULT, _ALPH, 1);
    mark_des(table, _DEFAULT, _PUN,  3);
    mark_des(table, _DEFAULT, _NUMB, 2);
    mark_des(table, _DEFAULT, _DOT,  3);
    mark_des(table, _DEFAULT, _INVALID, 0);
    mark_des(table, _DEFAULT, _NULL, -1);
    //ALPH
    mark_des(table, _ALPH, _ALPH, 1);
    //PUN
    
    //NUMB
    mark_des(table, _NUMB, _DOT, 4);
    mark_des(table, _NUMB, _NUMB, 2);
    //DOT
    mark_des(table, _DOT, _NUMB, 4);
}

void go_next_pos(const string& _str, string::iterator& _pos){
    assert(_pos != _str.end() && "Error [go_next_pos]: Reach the end of string");

    if(_pos != _str.end());
        _pos++;
};

int get_next_state(int table[][MAX_COL],const string& _str, const string::iterator& _pos, int current_state){
    assert(_pos != _str.end() && "Error [get_next_state]: Reach the end of string, no next state");
 
    string::iterator next = _pos + 1;
    int _input = input(*next);
    int next_state = get_des(table, current_state, _input);

    return next_state;
}
