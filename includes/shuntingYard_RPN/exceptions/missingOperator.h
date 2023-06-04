#ifndef SYRPN_EXCEPTION_MISSINGOPERATOR
#define SYRPN_EXCEPTION_MISSINGOPERATOR

#include "../token/token.h"


class Exception_MissingOperator
{
    
public:
    Exception_MissingOperator(Token* ptr = nullptr){
        _ptr = ptr;
    }

    Token*  _ptr;
};


#endif