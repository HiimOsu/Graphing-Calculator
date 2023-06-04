#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <cassert>
using namespace std;

#include "const.h"

//Type of token:
/*
enum Token_Type{

TYPE_EMTPY_DEFAULT  = 0
    child:
        TYPE_INTEGER        = 1,
        TYPE_ALPHA/TYPE_VARIABLE = 3,
        TYPE_OPERATOR       = 4,
            child: 
                TYPE_FUNCTION       = 2,
        TYPE_LEFT_PARAN     = 5,
        TYPE_RIGHT_PARAN    = 6,

};


*/

class Token{
public:
    Token();

    virtual
    char tok();
        
    virtual
    int type();

    virtual 
    string str_tok();

    void print(ostream& outs) const;
    friend ofstream&  operator <<(ofstream& outs, const Token& print_me);
protected:
    string _tok;
    Token_Type _type;
};




#endif  