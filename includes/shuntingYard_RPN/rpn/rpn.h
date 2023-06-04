#ifndef RPN_H
#define RPN_H

#include    <iostream>
using   namespace std;

//include queue
#include    "../queue/MyQueue.h"
#include    "../stack/MyStack.h"
//include token
#include    "../token/const.h"
#include    "../token/token.h"
#include    "../token/function.h"
#include    "../token/integer.h"
#include    "../token/operator.h"
#include    "../token/leftparen.h"
#include    "../token/rightparen.h"
//Excpetion
#include    "../exceptions/excptions.hpp"

class RPN{
public:
    //Post: input_postfix: None
    RPN();

    //Post: input_postfix: postfix
    RPN(const Queue<Token*>& postfix);

    //==========operator
    //Pre:  intput_postfix is not empty, and
    //          the expression is in reverse polish notation(rpn)
    //           Cannot handle parenthesies, [DONT INCLUDE ')' or '(' !!!];  
    //Post: return evaluatioin of _postfix expression
    double  operator ()(double x = 0) throw(Exception_MissingOperands,Exception_MissingOperator, Exception_EmptyExpression);
    //==========Functions
    void    set_input(const Queue<Token*>& postfix);
    bool    is_empty();
private:
    Queue<Token*> _postfix;

};

double  evaluate_operator(Queue<Token*>::Iterator& current_tok, Stack<double>& result) throw (Exception_MissingOperands,Exception_MissingOperator);
#endif  