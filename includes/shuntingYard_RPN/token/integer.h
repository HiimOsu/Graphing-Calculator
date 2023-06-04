#ifndef TOKEN_INTEGER_H
#define TOKEN_INTEGER_H

#include "token.h"
#include "const.h"

class Integer: public Token
{
public:
    Integer(): Integer(0){}
    Integer(int tok){
        _tok    = to_string(tok);
        _type   = TYPE_INTEGER;
        _val    = tok;
    }

    int val(){ return _val;}

private:
    int _val;
};

#endif