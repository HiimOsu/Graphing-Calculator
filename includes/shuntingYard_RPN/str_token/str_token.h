#ifndef STR_TOKEN_H
#define STR_TOKEN_H

#include <string>
#include "table_functions/table_functions.h"
using namespace std;

class StrToken{
public:
    StrToken();
    StrToken(string input);

    //=============Accessor (modifies _str, and _pos)
    string get_token(char* str, char* stop_str);
    
    string get_token();
    //Pre:None
    //Post: Return the first remaining token
    
    string get_token(string new_str);
    //Pre:None
    //Post:Reset _str to new_str, and return the first token

    void set_string(string new_str);
    //Pre:None
    //Post:Reset _str to new_str. 
    

    //==============Accessor    (Did not modify)
    string read_str() const;
    //Pre: None
    //Post: return the whole string

    int last_token_type();
    int this_token_type();
    //Pre:None
    //Post: if there is no token in the string return true, else return false;
    bool is_empty();
    
private:
    int table[MAX_ROW][MAX_COL];
    int _last_token_type; 
    int _this_token_type;
    string::iterator _pos;       //Store the next position of last token.
    string _str;

    int get_input() const;      //
    int input(char c) const;    //return the type of Input(c)

    int get_next_state(int current_state) const;
    void go_next_pos();
    void makeTable();

};


#endif