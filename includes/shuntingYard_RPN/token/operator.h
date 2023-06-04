#ifndef TOKEN_OPERATOR_H
#define TOKEN_OPERATOR_H

#include "token.h"

class Operator: public Token
{
public:
    Operator(){
        Operator("Error");
    }
    Operator(string tok){
        _tok    = tok;
        _type   = TYPE_OPERATOR;

        switch (tok.at(0))
        {
        case '^':
            _precedence = 4;
            num_argu    = 2;
            break;
        case '*':
        case '/':
            _precedence = 3;
            num_argu    = 2;
            break;
        case '+':
        case '-':
            _precedence = 2;
            num_argu    = 2;
            break;
        default:
                _precedence = 0;
                num_argu    = 0;
            break;
        }
    }

    int precedence(){
        return _precedence;
    }
    int num_arguments(){
        return num_argu;
    }
protected:
    int _precedence;
    int num_argu;
};

#endif