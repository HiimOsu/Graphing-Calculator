#include "tk_string.h"

Tk_String::Tk_String(string buffer){
    _buffer = buffer;
}

Queue<Token*> Tk_String::getQueue_Token()  throw (Exception_MissingOperands, Exception_MissingOperator){
    if(_buffer.empty()){
        return Queue<Token*>();
    }
    // assert(!_buffer.empty());
    const bool debug = false;

    string buff = _buffer;
    StrToken t(buff);
    Queue<Token*> result;
    while(!t.is_empty()){
    buff = t.get_token();
    string str = buff;
    string::iterator it_str = str.begin();

        switch (t.this_token_type())
        {
        case _ALPH:
            
            while(it_str != str.end()){
                *it_str = *it_str & ~(32);
                it_str++;
            }

            //  Functions:
            if(str == "SIN"){
                result.push(new Function(buff, FUNC_TYPE_SIN));
            }
            else if(str == "COS"){
                result.push(new Function(buff, FUNC_TYPE_COS));
            }
            else if(str == "TAN"){
                result.push(new Function(buff, FUNC_TYPE_TAN));
            }
            else if(str == "CSC"){
                result.push(new Function(buff, FUNC_TYPE_CSC));
            }
            else if(str == "COT"){
                result.push(new Function(buff, FUNC_TYPE_COT));
            }
            else if(str == "SEC"){
                result.push(new Function(buff, FUNC_TYPE_SEC));
            }
            else if(str == "LOG"){
                result.push(new Function(buff, FUNC_TYPE_LOG));
            }
            else if(str == "LN"){
                result.push(new Function(buff, FUNC_TYPE_LN));
            }
            else if(str == "NEG"){
                result.push(new Function("$", FUNC_TYPE_NEG));
            }
            else if(str == "ABS"){
                result.push(new Function(buff, FUNC_TYPE_ABS));
            }
            else if(str == "MIN"){
                result.push(new Function(buff, FUNC_TYPE_MIN));
            }
            else if(str == "MAX"){
                result.push(new Function(buff, FUNC_TYPE_MAX));
            }
            else if(str == "EXP"){
                result.push(new Function(buff, FUNC_TYPE_EXP));
            }
            //  Variable/Constants:
            else {
                result.push(new Variable(buff));

            }
            break;

        case _PUN:
            if(debug){
                
                cout << "_PUN_tok: " << buff << endl;
            }
            
            if(buff == "-"){
                result.push(new Function("$", FUNC_TYPE_NEG));
            }
            else
            {
                switch(buff.at(0)){
                case '(':
                result.push(new LeftParen(buff));
                break;
                case ')':
                result.push(new RightParen(buff));
                break;

                default:
                result.push(new Operator(buff));
                }
            }

            break;
        case _NUMB:
            if(debug){
                cout << "_NUMB_tok: " <<  buff <<endl;
            }
            int integer = 0;

            for(int i = 0; i < buff.length(); i++){
                integer += (buff.at(i) - '0') * pow(10, buff.length() - i -1);
                // cout << "(buff.length() - i -1): " << (buff.length() - i -1) << endl
                //     << "buff at: " << buff.at(i) << endl;
            }
            result.push(new Integer(integer));
        }
    }

    try{
        result = check_unaryOperator(result);
    }    
    catch(Exception_MissingOperands e){
        throw Exception_MissingOperands(e);
    }
    catch(Exception_MissingOperator e){
        throw Exception_MissingOperator(e);
    }
    

    return result;
}

void Tk_String::set_input(string buffer){
    _buffer = buffer;
}  

string Tk_String::check_DefineFunction(string alph){


}

Queue<Token*> Tk_String::check_unaryOperator(Queue<Token*>& uncheck_infix) throw (Exception_MissingOperands, Exception_MissingOperator)
{
    const bool debug = false;
    Queue<Token*>::Iterator prv_it = uncheck_infix.begin(), cur_it;
    if(uncheck_infix.empty()){
        return uncheck_infix;
    }
    
    cur_it = prv_it;
    cur_it++;

    if(cur_it == uncheck_infix.end()){// One Token in Infix
        //If it is not a "x" or a constant like "1" 
        if((*prv_it)->type() != TYPE_VARIABLE && (*prv_it)->type() != TYPE_INTEGER){
            throw Exception_MissingOperands(*prv_it);
        }
        return uncheck_infix;
    }
    

    bool check_for_unaryOperator = false;
    // if((*prv_it)->str_tok() == "-"){    //If first token is '-', make it into a unary -
    //     delete *prv_it;
    //     *prv_it = new Function("$",FUNC_TYPE_NEG);
    // }
    int count =0;
    while (cur_it != uncheck_infix.end())
    {
        if((*cur_it)->str_tok() == "$"){
            // if(debug)
            //     cout << "Debug: Checking Unary" << endl;
            check_for_unaryOperator = false;
            Queue<Token*>::Iterator next_it = cur_it;
            next_it ++;
            if(next_it.is_null()){
                //InCorrect expression
                // '-' always have right operands
                throw Exception_MissingOperands(*prv_it);
            }

            switch ((*prv_it)->type())
            {
                case TYPE_RIGHT_PARAN:
                case TYPE_VARIABLE:
                case TYPE_INTEGER:
                    switch ((*next_it)->type())
                    {
                        case TYPE_LEFT_PARAN:
                        case TYPE_VARIABLE:
                        case TYPE_INTEGER:
                        case TYPE_FUNCTION:
                            delete *cur_it;
                            uncheck_infix.replace(cur_it, static_cast<Token*> (new Operator("-")));

                            break;
                        case TYPE_OPERATOR:
                        case TYPE_RIGHT_PARAN:
                            //ThrowExceptio
                            break;
                    }
                    break;
                case TYPE_FUNCTION:
                    if((*prv_it)->tok() == '$'){
                        uncheck_infix.insert_after(prv_it,  static_cast<Token*>  (new LeftParen()));
                        count++;
                        prv_it++;
                    }
                    else
                    switch ((*next_it)->type()){
                        case TYPE_VARIABLE:
                        case TYPE_INTEGER:
                            uncheck_infix.insert_after(prv_it,  static_cast<Token*>  (new LeftParen()));
                            uncheck_infix.insert_after(next_it,  static_cast<Token*> (new RightParen()));
                            prv_it++;
                            break;
                    }
                
                    
            }
        }

        switch((*cur_it)->type()){
            case TYPE_ALPHA:
            case TYPE_INTEGER:
                while(count != 0){
                    uncheck_infix.insert_after(cur_it,  static_cast<Token*>  (new LeftParen()));
                    count--;
                }
            break;
        }
        cur_it++;
        prv_it++;
    }
    
    return uncheck_infix;
}


int Tk_String::pow(int base, int power){
    int result = 1;
    for(int i = 0; i < power; i++){
        result *= base;
    }
    return result;
}