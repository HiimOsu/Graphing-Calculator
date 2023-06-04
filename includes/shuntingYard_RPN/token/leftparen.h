#ifndef TOKEN_LEFTPAREN_H
#define TOKEN_LEFTPAREN_H

#include "token.h"

class LeftParen: public Token
{
public:
    LeftParen(string tok = "("){
        _tok    = tok;
        _type   = TYPE_LEFT_PARAN;
    }

};

#endif