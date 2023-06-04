#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
using namespace std;
#include "../token/token.h"

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

class ShuntingYard{
public: 
    ShuntingYard();
    ShuntingYard(Queue<Token*> infix);

    Queue<Token*> postfix();    
    Queue<Token*> postfix(Queue<Token*> infix);
    void infix(Queue<Token*> new_infix);
    
private:
    Queue<Token*> _infix;
};

#endif