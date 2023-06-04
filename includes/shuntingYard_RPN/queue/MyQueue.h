#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
//================================================================================================
//Iterator class
   
    class Iterator{
    public:
        friend class Queue;                         //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                    //default ctor
        Iterator(node<T>* p){_ptr = p;}             //Point Iterator to where
                                                    //  p is pointing to

        T& operator *(){
            assert(! is_null() && "Error: [operator *()]");    //assert(is not null);
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
            // cout << "Debug [queue postfix ++()]: *it == " << *it << endl << endl;
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
    Queue(){
        _front  = nullptr;
        _rear   = nullptr;
        _size   = 0;
    }

    //Big3
    Queue(const Queue<T>& copyMe){
        _size   = copyMe._size;
        _front  = _copy_list(copyMe._front);
        _rear   = _last_node(_front);
    }
    ~Queue(){
        _clear_list(_front);
    }
    Queue& operator=(const Queue<T>& RHS){
        if(&RHS == this){
            return *this;
        }
        if(!empty()){
            _clear_list(_front);
        }

        _size   = RHS._size;
        _front  = _copy_list(RHS._front);
        _rear   = _last_node(_front);

    }

//================================================================================================
//Accessor[type T]
    bool empty() const{
        if(_size == 0){
            return true;
        }
        return false;
    }
    T front() const{
        assert(!empty() && "Error[T front()]: cannot return empty queue");
        return _front->_item;
    }
    T back()const{
        assert(!empty() && "Error[T back()]: cannot return empty queue");
        return _rear->_item;
    }

//================================================================================================
//Modifer
    void push(T item){
        
        _insert_after(_front, _rear, item);
        
        if(empty()){//if list is empty _front = _rear
            _rear = _front;
        }else{
            _rear = _rear->_next;
        }
        
        ++_size;
    }

    T pop(){
        assert(!empty() && "Error [Queue:: pop()]: Poping from an empty queue");
        T item;
    
        item    = _delete_node(_front, _front);
        --_size;
        return item;
    }

//================================================================================================
//Accessor[type Iterator]
    Iterator begin() const{return Iterator(_front);}            //Iterator to the head node
    Iterator end() const{return Iterator();}                    //Iterator to NULL
    
    //insert the
    Iterator insert_after(Iterator after_this, T item){
        node<T>* node = _insert_after(_front, after_this._ptr, item);
        return Iterator(node);
    }

   Iterator replace(Iterator replace_this, T item){
        node<T>* node = replace_this._ptr;
        node->_item = item;
        return Queue<T>::Iterator(node);
    }
//================================================================================================
//General Accessor
    //cout Queue
    void print_pointers(){
        _print_list(_front);
    }
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);

private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};


template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){
    outs << "Front: ";
    _print_list(printMe._front, outs);
    return outs;   
}



#endif