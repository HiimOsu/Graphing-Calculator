#ifndef RPN_CONST_H
#define RPN_CONST_H


enum Token_Type{
TYPE_EMTPY          = 0,
TYPE_INTEGER        = 1,
TYPE_FUNCTION       = 2,
TYPE_ALPHA          = 3, TYPE_VARIABLE = 3,
TYPE_OPERATOR       = 4,
TYPE_LEFT_PARAN     = 5,
TYPE_RIGHT_PARAN    = 6,

};

enum Function_Type{
    FUNC_TYPE_SIN   = 0,
    FUNC_TYPE_COS,       
    FUNC_TYPE_TAN,
    FUNC_TYPE_SEC,
    FUNC_TYPE_CSC,
    FUNC_TYPE_COT,   
    FUNC_TYPE_LOG,          //Log with base 
    FUNC_TYPE_LN,           //Natural Log
    FUNC_TYPE_NEG, 
    FUNC_TYPE_EXP,  
    FUNC_TYPE_ABS,  
    FUNC_TYPE_MAX,  
    FUNC_TYPE_MIN,  

};

const int NUMBER_OF_ARUGMENT[] = {
    1,      //SIN  
    1,      //COS
    1,      //TAN
    1,      //SEC
    1,      //CSC
    1,      //COT
    2,      //LOG
    1,      //LN
    1,      //NEG
    1,      //EXP
    1,      //ABS
    2,      //MAX
    2,      //MIN
};

enum StrTokenType{
    _DEFAULT = 0,
    _ALPH    = 1,
    _NUMB    = 2,
    _PUN     = 3,
    _DOT     = 4,
    _INVALID = 5,
    _NULL    = 6
};

//20 digits after decimals
const double CONSTANT_E = 2.71828182845904523536; 
const double CONSTANT_PI = 3.1415926535897932384;
//Tylor series approximation:
#endif