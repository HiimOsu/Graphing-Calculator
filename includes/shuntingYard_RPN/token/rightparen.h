#ifndef TOKEN_RIGHTPAREN_H
#define TOKEN_RIGHTPAREN_H

#include "token.h"

class RightParen: public Token
{
public:
    RightParen(string tok = ")"){
        _tok    = tok;
        _type   = TYPE_RIGHT_PARAN;
    }

};

#endif