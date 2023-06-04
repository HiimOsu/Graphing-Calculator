#ifndef VARIABLE_H
#define VARIABLE_H

#include "token.h"

class Variable: public Integer{
public:
    Variable(string tok = "x"){
        _tok = tok;
        _type = TYPE_VARIABLE;
    }
};

#endif