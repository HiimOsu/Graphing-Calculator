#ifndef MYSTACK_H
#define MYSTACK_H

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack{
public:
//================================================================================================
//Iterator class
   
    class Iterator{
    public:
        friend class Stack;                         //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                    //default ctor
        Iterator(node<T>* p){_ptr = p;}             //Point Iterator to where
                                                    //  p is pointing to

        T& operator *(){
            assert(! is_null() && "Error: [Stack::Iterator::operator *()]");    //assert(is not null);
            return _ptr->_item;
        }
        
        T* operator ->(){
            assert(! is_null() && "Error: [operator ->()]");
            return &(_ptr->_item);
        }
        
        operator bool(){
            return _ptr != nullptr;
        }

        bool is_null(){
            return _ptr == nullptr;
        }
        
        //Prefix ++it
        Iterator& operator++(){
            assert(! is_null() && "Error: [Prefix operator ++()]");
            _ptr = _ptr->_next;
            return *this;
        }

        //Postfix it++
        friend Iterator operator++(Iterator& it, int unused){
            assert(! it.is_null() && "Error: [Postfix operator ++()]");
            Iterator temp(it);
            it._ptr = it._ptr->_next;
            return temp;
        }

        friend bool operator !=(const Iterator& LHS, const Iterator& RHS){
            return LHS._ptr != RHS._ptr;
        }

        friend bool operator ==(const Iterator& LHS, const Iterator& RHS){
            return !(LHS != RHS);
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

//================================================================================================
//Constor
    Stack(){
        _top    = nullptr;
        _size   = 0;
    }
    
    //Big 3
    Stack(const Stack<T>& copyMe){
        _size   = copyMe._size;
        _top    = _copy_list(copyMe._top);
    }
    
    ~Stack(){
        _clear_list(_top);
    }
    
    Stack<T>& operator=(const Stack<T>& RHS){
        if(RHS._top == this->_top){
            return *this;
        }
        
        if(!empty()){
            _clear_list(_top);
        }

        _size   = RHS._size;
        _top    = _copy_list(RHS._top);
        return *this;
    }

//================================================================================================
//Accessor && Modifiers

    //-------------------------------------
    //              T top()
    //Pre: None
    //Post: Return the data stores in top
    T top() const{
        return _top->_item;
    }

    //------------------------------------
    //              bool empty()
    //Pre: None
    //Post: Return True if the stack is empty, else return false;
    bool empty() const{
        return _top == nullptr;
    }

    //------------------------------------
    //              void push(T item)
    //Pre: None
    //Post: Push the item into the stack and increment the size
    void push(T item){
        _size++;
        _insert_head(_top, item);
    }

    // ----------------------------------
    //              T   pop()
    //Pre:  Stack cannot be empty
    //Post: Pop the top of the stack, and return the item inside it
    T pop(){
        assert(!empty() && "Error[Stack::pop()] popping an empty Stack");

        T item = *begin();

        _delete_node(_top,_top);
        _size--;

        return item;
    }


    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe);
    
    Iterator begin() const{                         //Iterator to the head node
        return Iterator(_top);
    }
    Iterator end() const{                           //Iterator to NULL
        return Iterator();
    }
    int size() const { 
        return _size;
    }

private:
    node<T>* _top;
    int _size;
};


template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe){
    if(printMe.empty()){
        outs << "[Empty Stack]";
    }

    _print_list<TT>(printMe._top, outs);
    return outs;
}


#endif