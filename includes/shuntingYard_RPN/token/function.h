#ifndef TOKEN_FUNCTION_H
#define TOKEN_FUNCTION_H

#include "iostream"
#include "operator.h"
using namespace std;
class Function: public Operator
{
public:
    Function(){
        Operator();
        _type   = TYPE_EMTPY;
    }
    Function(string tok, Function_Type func_type){
        _tok    = tok;
        _type   = TYPE_FUNCTION;
        _func_type = func_type;
        
        if(func_type == FUNC_TYPE_NEG){
            _precedence = 5;
        }
        else _precedence = 6;

        if(func_type >=0 ){
            num_argu = NUMBER_OF_ARUGMENT[func_type];
        }else num_argu = 0;
    }

    int get_func_type(){
        return _func_type;
    }

private:
    Function_Type _func_type;

};

#endif