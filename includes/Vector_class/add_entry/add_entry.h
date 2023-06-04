#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include <cassert>
#include "../array_functions/array_functions.h"


//Precondition:
    //capacity > 0
    //size > 0 for erase,remove,remove_last_entry, 
        //size >= 0 for insert,add_entry
    //list cannot be nullptr

template <class T>
T* insert_entry(T* list,const T& value, int index, 
                                        int& size, int& capacity);  // insert "value" at
                                                                    // a[index]
                                                                    //if size == capacity
                                                                    //double its capacity;
template<class T>
T* add_entry(T* list, const T& value, int& size, int& capacity);              //append "value" to a

template <class T>
T* remove_entry(T* list, const T& value, int& size, int& capacity);           //remove the FIRST entry 
                                                                    //contains "value"
                                                                    //if size == (1/4)capacity
                                                                    //reduce its capacity to half

//Remove the item at arr[index]
//Order the item and reallocate the array itself
template <class T>
T* erase_entry(T* list, int index, int& size, int& capacity);          //remove the item at
                                                                    //a[index]

template <class T>
T* remove_last_entry(T* list, T& popped, int& size, int& capacity);     //remove the LAST entry 
                                                                    //and put the value inside the entry into item




template <class T>
T* insert_entry(T* a, const T& value, int index, int& size, int& capacity){//tested
    //assert(capacity >= 3 && "Capacity should always at least 3");
    assert(a != nullptr && "cannot insert entry into a nullptr");
    assert((index < size || index == 0) && "Cannot insert entry out of range");
    assert(index >= 0 && "Cannot insert at negative position");

    if(size == capacity){
        capacity = 2 * capacity;
        a = reallocate <T> (a,size,capacity);
    }

    //make a hole
    if(size != 0)
        shift_right(a,size,index); 
    
    T* here = a + index;
       
    *here = value;             //fill that hole with "value"
    
    return a;
}

template<class T>
T* add_entry(T* a, const T& value, int& size, int& capacity){//tested
    //assert(capacity >= 3 && "Capacity should always at least 3");
    if(size == capacity){
        capacity = 2 * capacity;
        a = reallocate <T> (a,size,capacity);
    }

    append(a,size,value);
    
    return a;
} 

template <class T>
T* erase_entry(T* a, int index, int& size, int& capacity, int min_cap){//tested
    //assert(capacity >= 3 && "Array's Capacity should be at least 3");
    assert(size > 0 && "Cannot erase entry with size less than  or equal to 0");
    assert(index < size && index >= 0 && "Cannot erase entry out of range");
    assert(a != nullptr && "Cannot erase nullptr");
    T* new_array = a;
    
    shift_left(a,size, index);

    if(size == 0)
        return a;


    if(capacity != min_cap){//capacity 
        int one_forth = (capacity/4);
        int _one_forth = one_forth;

        while(size <= _one_forth){  //If the size is <= one_forth of the capacity, reduce capacity
            
            if(capacity / 2 >= min_cap)
                capacity = capacity / 2;
            else capacity = min_cap;

            _one_forth = (capacity/4);
        }


        if(size <= one_forth){//If the size is <= one_forth of the capacity, reduce capacity

            new_array = reallocate <T> (a,size,capacity);

        }
    }

    return new_array;
}        

template <class T>
T* remove_entry(T* a,const T& value, int& size, int& capacity, int min_cap){//tested
    //assert(capacity >= 3 && "Array's Capacity should be at least 3");
    assert(size > 0 && "Cannot remove entry with size less than  or equal to 0");
    assert(a != nullptr && "Cannot remove nullptr");

    T* here = search_entry(a, size, value);

    if(here == nullptr){
        return a;
    }

    int index = here - a;

    a = erase_entry(a,index, size, capacity, min_cap);
    
    return a;
}

template <class T>
T* remove_last_entry(T* a, T& item, int& size, int& capacity, int min_cap){
    // T* walker = a;
    // T* end_walker = a + size - 1;
    // int index = search(walker, size, value);

    // if(index == -1)
    //     return a;


    // walker = a + index;

    // while(walker != end_walker){
    //     if(search(walker + 1, size - index - 1, value) != -1){
    //         index = search(walker + 1, size - index - 1, value) + index + 1;
    //         walker = a + index;
    //     }
    //     else walker = end_walker;
    // }
   
    //assert(capacity >= 3 && "Array's Capacity should be at least 3");
    assert(size > 0 && "Cannot remove entry with size less than  or equal to 0");
    assert(a != nullptr && "Cannot remove nullptr");

    T* last = a + size - 1;
    item = *last;    

    a = erase_entry(a, size-1, size, capacity, min_cap);
   
    return a;
}   

#endif