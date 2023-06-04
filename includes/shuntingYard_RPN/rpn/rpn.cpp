#include    "rpn.h"
#include    "../token/const.h"
#include    "cmath"
//=========constructor
RPN::RPN(){
    return;
}

RPN::RPN(const Queue<Token*>& postfix){
    _postfix = postfix;
}

//===========Operator
double RPN::operator ()(double x) throw(Exception_MissingOperands,Exception_MissingOperator, Exception_EmptyExpression)
{
    const bool  debug = false;
    if(is_empty()){
        throw Exception_EmptyExpression();
    }
    // assert(!is_empty() && "Error[RPN::operator()]: Input is empty");
    
    /*
    Token Type:
    TYPE_EMTPY          = 0, (NOT USED in this function)
    TYPE_INTEGER        = 1,
    TYPE_FUNCTION       = 2,
    TYPE_OPERATOR       = 3,
    TYPE_LEFT_PARAN     = 4, (NOT USED in this function)
    TYPE_RIGHT_PARAN    = 5  (NOT USED in this function)
  */
    Queue<Token*>::Iterator it = _postfix.begin();
    Stack<double> _stack;
    string tok;
    string::iterator it_str;
    while(it != _postfix.end()) {
        tok = (*it)->str_tok();
        it_str = tok.begin();
        while(it_str != tok.end()){         //To UpperCase
            *it_str = *it_str & ~(32);
            it_str++;
        }

        switch ((*it)->type()){             //Evaluate depends on Token Type
            case TYPE_INTEGER:                  //Integer
                _stack.push(static_cast<Integer*>(*it)->val());
                break;

            case TYPE_VARIABLE:                 //Variable
                if(tok == "E"){
                    _stack.push(CONSTANT_E);
                }
                else if (tok == "PI"){
                    _stack.push(CONSTANT_PI);
                }
                else _stack.push(x);  
                break;

            case TYPE_FUNCTION:
            case TYPE_OPERATOR: 
                try{
                    evaluate_operator(it, _stack);
                }
                catch(Exception_MissingOperands e){
                    throw Exception_MissingOperands(e._ptr);
                }
                catch(Exception_MissingOperator e){
                    throw Exception_MissingOperator(e._ptr);
                }
                break;
        }
        it++;
    }

    if(_stack.size() != 1){
        throw Exception_MissingOperator();
    }

    return _stack.pop();
}


//===========fuctions
void RPN::set_input(const Queue<Token*>& postfix){
    // if(!is_empty()){//if the postfixueue is not empty
    //     Queue<Token*>::Iterator it1 = _postfix.begin();
    //     while(! it1.is_null())//if it is not the end of the postfixueue)
    //     {
    //         delete *it1++;
    //     }
    // }
    _postfix  = postfix;
}


bool RPN::is_empty(){
    return _postfix.empty();
}

double  evaluate_operator(Queue<Token*>::Iterator& current_tok, Stack<double>& result)
throw(Exception_MissingOperands,Exception_MissingOperator)
{
    double o1,o2,o3;
    //Get operands
    //For example '+'operator  1 + 2  have two arguments,
    //And operand#1, o1 = 1 and o2 = 2
    switch(static_cast<Operator*>(*current_tok)->num_arguments()){
        case 1:
            if(result.size() < 1){
                throw Exception_MissingOperands(*current_tok);
            }
            assert(result.size() >= 1 && "Missing Operands!");
            o1 = result.pop();
            break;
        case 2:
            if(result.size() < 2){
                throw Exception_MissingOperands(*current_tok);
            }
            assert(result.size() >= 2 && "Missing Operands!");
            o2 = result.pop();
            o1 = result.pop();
            break;
        case 3:
            if(result.size() < 3){
                throw Exception_MissingOperands(*current_tok);
            }
            assert(result.size() >= 1 && "Missing Operands!");
            o3 = result.pop();
            o2 = result.pop();
            o1 = result.pop();
    }
    
    
    if((*current_tok)->type() == TYPE_FUNCTION){
        //Function Evaluation
        switch (static_cast<Function*>(*current_tok)->get_func_type())
        {
            case FUNC_TYPE_SIN:
                o1 = sin(o1);
                break;
            case FUNC_TYPE_COS:
                o1 = cos(o1);
                break;
            case FUNC_TYPE_TAN:
                o1 = tan(o1);
                break;
            case FUNC_TYPE_LN:
                
                o1 = log(o1);
                break;
            case FUNC_TYPE_LOG:
                o1 = log(o2) /log(o1);
                break;
            case FUNC_TYPE_NEG:
                o1 = -o1;
                break;
            case FUNC_TYPE_SEC:
                o1 = 1.f / cos(o1);
                break;
            case FUNC_TYPE_CSC:
                o1 = 1.f / sin(o1);
                break;
            case FUNC_TYPE_COT:
                o1 = 1.f / tan(o1);
                break;
            case FUNC_TYPE_ABS:
                o1 = abs(o1);
                break;
            case FUNC_TYPE_EXP:
                o1 = exp(o1);
                break;
            case FUNC_TYPE_MAX:
                o1 = max(o1,o2);
                break; 
            case FUNC_TYPE_MIN:
                o1 = min(o1, o2);
                break; 
            default:
                break;
        }

    }else{
        //Operator Evaluation
        switch((*current_tok)->tok()){           //check operator type
            case '+':
                o1 += o2;
                break;
            case '-':
                o1 -= o2;
                break;
            case '*':
                o1 *= o2;
                break;
            case '/':
                // assert(o2 && "Error [operator()]: (Token_type == operator '/') Dividing by 0");
                o1 /= o2;
                break;
            case '^':
                o1 = pow(o1,o2);
                break;
        }   
    }
        result.push(o1);

    return o1;
}


