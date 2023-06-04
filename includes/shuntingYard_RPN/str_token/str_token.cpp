#include "str_token.h"


//=====CONSTRUCTOR=====================================================================//
StrToken::StrToken(){
    makeTable();
    set_string("");
    _last_token_type = 0;
    _this_token_type = 0;
}

StrToken::StrToken(string str){
    makeTable();
    set_string(str);
    _last_token_type = 0;
    _this_token_type = 0;
}



//=====Get token=====================================================================//

string StrToken::get_token(){
    if(is_empty())
        return "";

    _last_token_type = _this_token_type;
    //Return the token: substr from the first_sucess to last_success state;    
    string::iterator last_success =  _pos;
    string::iterator first_success = _pos;
    
    int _input = get_input();
    int current_state = get_des(table, 0, _input);
    int last_state = current_state;                 //Determine the state of last_success_state before the fail state                

    bool fSucess_is_set = false;
    bool sucess;

    while(current_state != -1){
        last_state = current_state;
        sucess = get_suc_fail(table, current_state);

        //If first sucess is not set, go save our First_sucess
        if(fSucess_is_set != true){                     
            if(sucess){
                first_success = _pos;
                fSucess_is_set = true;
            }
        }
        
        if(sucess){//set Last_sucess
            last_success = _pos;   
        }

        go_next_pos();
        _input = get_input();
        current_state = get_des(table, current_state, _input);
        
        if(current_state == 4){
            if(last_state == 2) {
                if(get_next_state(current_state) == -1)
                    current_state = -1;
            }
        }
    
    }

    string str_type;
    _this_token_type = last_state;

    switch(last_state){
        case -1:     str_type = "[Empty]";           break;
        case  1:     str_type = "[ Word ]";          break;
        case  2: case 4: str_type = "[ Numb ]";      break;
        case  3:     str_type = "[ Punc ]";          break;
        case  6: default: str_type = "[ Invalid ]";  break;
        
    }
    string return_me = _str.substr(first_success - _str.begin(), (last_success - first_success) + 1 );


    return return_me;
   
}

string StrToken::get_token(string new_str){
    set_string(new_str);
    return get_token();
}

//======Setter=====================================================================//
void StrToken::set_string(string new_str){
    _str = new_str;
    _pos = _str.begin();
}

//======Accessor===================================================================//

string StrToken::read_str() const{
    return _str;
}

int StrToken::last_token_type(){
    return _last_token_type;
}
int StrToken::this_token_type(){
    return _this_token_type;
}
bool StrToken::is_empty(){
    // cout << "Debug StrToken::is_empty(), current *_pos: " << *_pos << endl;
    return _pos == _str.end();
}

//==============Private Functions==========//
int StrToken::get_input() const{
    return input(*_pos);
}

int StrToken::input(char c) const{
    // const bool debug = false;
    const int //State
    _DEFAULT = 0,
    _ALPH    = 1,
    _NUMB    = 2,
    _PUN     = 3,
    _DOT     = 4,
    _INVALID = 5,
    _NULL    = 6;
    if(c == '\0'){
        // if(deubg)
        // cout << "Debug input: Char c: [" << c << "]" << endl;
        return _NULL;
    }  
    switch(c){ 
        case '*': case '+': case '-': case '/':
        case '^': case '(': case ')':
        return _PUN;
        
        
        default:
        break;
    }
    
    if(c == '.')
        return _DOT;
    //NUMBER
    if(c >= 48 && c <= 57)      //ASCII: 0-9 (48 - 57) NUMB
        return _NUMB;
    //ALPHA
    if(c >= 65 && c <= 90)      //ASCII: A-Z (65 - 90) ALPH
        return _ALPH;
    if(c >= 97 && c <= 122)     //ASCII: a-z (97 - 122) ALPH
        return _ALPH;

    return _INVALID;
}

void StrToken::makeTable(){
    const int NUM_STATE = 7;
    const int NUM_INPUT = 7;
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
    // mark_success(table, _DOT);

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

void StrToken::go_next_pos(){
    assert(_pos != _str.end() && "Error [go_next_pos]: Reach the end of string");

    if(_pos != _str.end());
        _pos++;
};

int StrToken::get_next_state(int current_state) const{
    assert(_pos != _str.end() && "Error [get_next_state]: Reach the end of string, no next state");
 
    string::iterator next = _pos + 1;
    int _input = input(*next);
    int next_state = get_des(table, current_state, _input);

    return next_state;
}