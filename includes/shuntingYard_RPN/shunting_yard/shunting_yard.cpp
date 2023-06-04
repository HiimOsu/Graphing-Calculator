#include "shunting_yard.h"

#include "../token/operator.h"

//======Constor
ShuntingYard::ShuntingYard(){
    return;
}

ShuntingYard::ShuntingYard(Queue<Token*> infix){
    _infix  = infix;
}
//======functions

Queue<Token*> ShuntingYard::postfix(){
    const bool debug = false;   
    Queue<Token*> output_que;       //output-queue
    Stack<Token*> s_operator;       //operator-stack
    Token* tok;                     //Token
    Stack<Token*>::Iterator o2;

    for(Queue<Token*>::Iterator it = _infix.begin(); it != _infix.end(); ++it){

        //ShuntingYard do different porc with different type of Token.
        switch((*it)->type()){
            //If it is a Variable, push it on to the output-Queue
            case TYPE_VARIABLE:         
                output_que.push(*it);
                break;
            //If it is an Integer, push it on to the output-Queue
            case TYPE_INTEGER:
                output_que.push(*it);
                break;
            
            //If it is a Function/Operator, then check the operator-Stack,
            //While the statck is not empty && the top is not Left-Paren '('
            //Pop the stack and push the operator into the output-Queue
            //EndWhile; Push the token Function/Operator onto the operator-Stack
            case TYPE_FUNCTION:                    
            case TYPE_OPERATOR:
                o2 = s_operator.begin();
                if(debug){
                    cout << "Debug, ShuntingYard::output_que(), [TYPE_OPERATOR], remaining stack: " << s_operator << endl;
                }
                while(o2 != s_operator.end() &&  (*o2)->tok() != '('){
                    
                    if( ( static_cast<Operator*> (*o2)->precedence() >= static_cast<Operator*>(*it)->precedence() )){
                        //Edge Case [Unary operatro '-']:
                        if(static_cast<Operator*> (*o2)->precedence() == FUNC_TYPE_NEG && static_cast<Operator*> (*it)->precedence() == FUNC_TYPE_NEG){
                            //do nothing
                            o2++;
                        }else
                        {
                            output_que.push(s_operator.pop());
                            o2 = s_operator.begin();
                        }
                    }else break;
                }
                s_operator.push(*it);
                break;
            //If it is a RightParen ')', then pop the operator-Stack 
            //and push popped item onto the output-Queue
            //Until top of the stack is '(' or Empty
            case TYPE_RIGHT_PARAN:
                tok  = s_operator.pop();
                while(tok ->tok() != '('){
                    if(debug){
                        cout << "Debug ,ShuntingYard::output_que(),[Right Parn],  Pushing stack.top(), top->tok(): " << tok ->tok() << endl;
                    }
                    output_que.push(tok);
                    tok   = s_operator.pop();
                }
                if(!s_operator.empty()){
                    tok  = *s_operator.begin();
                    if(tok ->type() == TYPE_FUNCTION){
                        output_que.push(s_operator.pop());
                    }
                }
                break;

            case TYPE_LEFT_PARAN:
                s_operator.push(*it);
                break;
        }
    }

    while(!s_operator.empty()){
        output_que.push(s_operator.pop());
    }
    
    return output_que;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> infix){
    ShuntingYard::infix(infix);
    return ShuntingYard::postfix();
}

void ShuntingYard::infix(Queue<Token*> new_infix){
    _infix = new_infix;
}