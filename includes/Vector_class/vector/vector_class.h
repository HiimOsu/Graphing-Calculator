#ifndef     VECTOR_CLASS_H
#define     VECTOR_CLASS_H

#include    <iostream>
#include    <iomanip>
#include    "../add_entry/add_entry.h"

using namespace std;
const int VECTORCLASS_MINIMUM_CAPACITY = 3;

template <class T>
class Vector{
public:
       
    class Iterator{
    public:
        friend class Vector;                         //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                    //default ctor
        Iterator(T* p){_ptr = p;}             //Point Iterator to where
                                                    //  p is pointing to

        T& operator *(){
            assert(! is_null() && "Error: [operator *()]");    //assert(is not null);
            return *_ptr;
        }
        
        T* operator ->(){
            assert(! is_null() && "Error: [operator ->()]");
            return (_ptr);
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
            _ptr++;
            return *this;
        }

        //Postfix it++
        friend Iterator operator++(Iterator& it, int unused){
            assert(! it.is_null() && "Error: [Postfix operator ++()]");
            // cout << "Debug [queue postfix ++()]: *it == " << *it << endl << endl;
            Iterator temp(it);
            it._ptr++;
            return temp;
        }

        friend bool operator !=(const Iterator& LHS, const Iterator& RHS){
            return LHS._ptr != RHS._ptr;
        }

        friend bool operator ==(const Iterator& LHS, const Iterator& RHS){
            return !(LHS != RHS);
        }

    private:
        T* _ptr;
    };


    //Creatate a vector by giving the starting capcity, default = 3
    Vector(int capacity = VECTORCLASS_MINIMUM_CAPACITY){
        assert(_capacity >= 0 && "Error: Constr(int = 100), capacity is negative");        
        const bool debug = false;
        
        set_capacity(capacity);        
        set_size(0);

    }
    
    Vector(T *arr, int size){
        assert(size >= 0 && "Error: Constr(T*, int), size is negative");
        const bool debug = false;

        set_capacity(0);
        set_capacity(size * 2);
        set_size(size);
        copy_array(_header, arr, _size);

    }
   

   //======================================================
   
   //big three
    Vector(const Vector& copy_me){
        const bool debug = false;

        *this = copy_me; 

    }
    
    ~Vector(){
        const bool debug = false;

        if(debug){
            cout << "DEBUG: DESTOR CALLED" << '\n';
        }

        if(_header != nullptr)
            delete[] _header;
    }
    
    Vector& operator =(const Vector& copy_me){
        if(this == &copy_me){
            return *this;
        }

        _min_cap = copy_me._min_cap;
        set_capacity(0);
        set_capacity(copy_me._capacity);
        set_size(copy_me._size);

        copy_array(_header, copy_me._header, _size);

        return *this;
        
    }

    //======================================================
   
    //member access functions:

    //Return the item by reference by the index provided 
    T& operator [](int index){ 
        assert((index >= 0 || index < _size) && "ERROR: operator[], index is out of in range");

        T *walker = _header + index;
        
        return *(walker);
    }
    
    //Return the item by reference by the index provided  (const)
    const T& operator [](int index) const{
        assert((index >= 0 || index < _size) && "ERROR: const operator[], index is out of range");
        
        T *return_me = _header + index;
        return *(return_me);
    }

    //Return the iterator of the item by the index provided 
    Iterator at(int index){                   //return reference to item at position index
        assert((index >= 0 || index < _size) && "ERROR: at(), index is out of range");
        
        return Iterator(_header + index);
    }
    
    //Return the iterator of the item by the index provided (const)
    const Iterator at(int index) const{       //return a const item at position index
        assert((index >= 0 || index < _size) && "ERROR: cosnt at(), index is out of range");        
        
        T* return_me = _header + index;
        return *return_me;
    }

    //Return the iterator of the begining of vector 
    Iterator begin(){                         //return iterator at position 0.
        return Iterator(_header);
    }

    //Return the iterator of the end of vector 
    Iterator end(){                          //return iterator at the end
        T* walker = _header + _size;     
        return Iterator(walker);
    }

    //Return the firts item by reference 
    T& front(){
        return *_header;
    }

    //Return the last item by reference 
    T& back(){
        return *(_header + _size -1);
    }
    //======================================================
   
    //Push and Pop functions:
   
   //Append item to the end and return &this
    Vector& operator +=(const T& item){     //push_back
        push_back(item);

        return *this;
    }
    //Append item to the end and return the iterator of that item
    Iterator push_back(const T& item){      //append to the end
        const bool debug = false;

        _header = add_entry <T>(_header, item, _size, _capacity);

        if(debug){
        }

        return Iterator(_header + _size -1);
    }
    //Remove the last item and return a coppy of the item
    T pop_back(){                       //remove last item and return it
        T item;
        if(_size > 0)
            _header = remove_last_entry(_header, item, _size, _capacity,_min_cap);
       
        return item;
    }
    
    //======================================================
    
    //Insert and Erase:
    
    Iterator insert(int insert_here, const T& insert_this){ //insert at pos
        assert(insert_here >= 0 && "Error: erase(), index is negative");
        assert(insert_here < size() || insert_here == 0 && "Error: erase(), index is out of range");
        
        if(insert_here + 1 > capacity()){
            set_capacity(insert_here + 1);
        }

        if(insert_here == 0 && size() == 0){
            return push_back(insert_this);
        }else
        if(size() < insert_here + 1 ){// insert nothing
            set_size(insert_here + 1);
        }

        _header = insert_entry(_header, insert_this, insert_here, _size, _capacity);

        return Iterator(at(insert_here));
    }
    
    //erase item at position
    //reallocate if necessary
    //Item would order itself and fill in the gap
    void erase(int erase_this_index){                   
        assert(erase_this_index >= 0 && "Error: erase(), index is negative");
        assert(erase_this_index < size() && "Error: erase(), index is out of range");
        
        if(erase_this_index + 1 > size()){//erase out of bound
            return;
        }

        _header = erase_entry(_header, erase_this_index, _size, _capacity, _min_cap);
    }
    
    Iterator index_of(const T& item){                        //search for item. retur index.
        return search<T>(_header, _size, item);
    }
    //======================================================
    
    //size and capacity:
    
    //Clear all the item in the vector and reallocate to minimum capacity
    void clear(){
        set_size(0);    
    }
    //Set the minimum capacity, min_cap =: 1 if given value < 0
    void set_min_capacity(int min_cap){
        if(_min_cap < 0){
            min_cap = 1;
        }
        _min_cap = min_cap;

        if(_capacity < _min_cap){
            set_capacity(_min_cap);
        }
    }
    
    //Set the vector size to desired size, reallocate memory if needed
    void set_size(int size){                    //enlarge the vector to this size
        assert(size >= 0 && "Error: set_size(), size cannot be negative.");
        if(size > _capacity){
            set_capacity(size);
        }

        assert(size <= _capacity && "set_size(): size cannot be set to larger than capacity");

        _size = size;

        return;
    }
    
    //Allocate space manually (if you want to reserve at least some space, use
    //  set_min_cap && set_capacity ,Else any functions that change size would reallocate automatically)
    void set_capacity(int capacity){            //allocate this space
        assert(capacity >= 0 && "Error: set_cap(), capcity cannot be negativ.");
        //special cases
        if(capacity == _capacity){
            return;
        }
        
        if(capacity == 0){
            if(this->_header != nullptr)
                delete[] _header;
            _header = nullptr;
            _capacity = 0;
            set_size(0);
            
            return;
        }
        //return here;

        //normal

        if(capacity < MINIMUM_CAPACITY){
             capacity   = MINIMUM_CAPACITY;
        }
        
        if(capacity < _size){
            set_size(capacity);
        }

        _capacity  = capacity;
        _header = reallocate <T> (_header, _size, _capacity);
    
    }
    
    //return size
    int size() const {return _size;}            //return _size
    //return capacity
    int capacity() const {return _capacity;}    //return _capacity
    //return bool isItEmpty
    bool empty() const{                         //return true if vector is empty
        if(_size == 0)
            return 1;
        else return 0;
    }
    
    //======================================================
    
    //OUTPUT:
    
    // template <class U>
    // friend std::ostream& operator <<(std::ostream& outs, const Vector<U>& _a);

    // template <class U>
    // friend string to_string(const U& vector);
    //======================================================
private:
    int _size = 0;
    
    int _capacity = 0;
    
    T* _header = nullptr;

    int _allocate_capacity; //This tell the class do not reduce the capacity even it can be reduced
    
    bool _fix_space = false;
    
    int  _min_cap = VECTORCLASS_MINIMUM_CAPACITY;


};

// template <typename U>
// std::ostream& operator <<(std::ostream& outs, const Vector<U>& _a)
// {
        
//         outs << to_string(_a);

//         return outs;
// }


// template <class U>
// string to_string(const U& vector){

//     return "(" + to_string(vector.size()) +  "/" + to_string(vector.capacity()) + ") " + array_string(vector._header, vector.size());
// }

#endif
