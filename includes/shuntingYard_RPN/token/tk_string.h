#ifndef TK_STRING_H
#define TK_STRING_H
#include <map>
#include "string"
using namespace std;

#include "../queue/MyQueue.h"
#include "../str_token/str_token.h"


#include "token.h"
#include "operator.h"
#include "integer.h"
#include "function.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "../exceptions/excptions.hpp"

class Tk_String{
public:
    Tk_String(string buffer = "");

    //PostCondition: Creatre a Queue<Token*>, and each elment are dynamic(new);
    Queue<Token*> getQueue_Token() throw (Exception_MissingOperands, Exception_MissingOperator);
    void set_input(string buffer);
    
    
private:
    string _buffer;
    int pow(int base, int power);

    //Check Defined Function
    string check_DefineFunction(string str);
    //Check the Unary operator in an Uncheck_infix token
    //Pre: recive a infix queue that all string '-' is subsitute by '$' unary neg operator token  
    //After checking every not unary operator '$' would turn into subtraction '-' 
    Queue<Token*> check_unaryOperator(Queue<Token*>& uncheck_infix)throw (Exception_MissingOperands, Exception_MissingOperator);


};

#endif
