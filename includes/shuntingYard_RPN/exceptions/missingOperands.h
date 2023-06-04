#ifndef SYRPN_EXCEPTION_MISSINGOPERANDS
#define SYRPN_EXCEPTION_MISSINGOPERANDS

#include "../token/token.h"
\

class Exception_MissingOperands
{

public:
    Exception_MissingOperands(Token* ptr = (nullptr)){
        _ptr = ptr;
    }

    Token*  _ptr;
};



#endif