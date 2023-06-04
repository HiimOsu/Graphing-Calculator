#include "token.h"

Token::Token(){
    _tok    = "\0";
    _type   = TYPE_EMTPY;
}

char Token::tok(){
    return _tok[0];
}

int Token::type(){
    return _type;
}

string Token::str_tok(){
    return _tok;
}
void Token::print(ostream& outs) const{
    outs << _tok;
}

ostream&  operator <<(ostream& outs,const Token print_me){
    print_me.print(outs);
    return outs;
}