#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <class ITEM_TYPE>
struct node{
public:
    node(const ITEM_TYPE& item = ITEM_TYPE(), node* next = nullptr):_item(item), _next(next){}

    template <typename T>
    friend ostream& operator <<(ostream& outs,const node<T> &printMe);


    //=====Memeber Variable=====
    ITEM_TYPE _item;
    node* _next;

};


template <typename T>
ostream& operator <<(ostream& outs,const node<T> &printMe){
    outs << printMe._item;
    return outs;                    
}

#endif