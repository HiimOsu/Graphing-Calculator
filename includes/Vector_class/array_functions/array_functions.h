#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include "iostream"
#include "string"
#include <cassert>

using namespace std;

namespace helper{
    //helper

    template<typename T>
    void swap(T* ptr1,T* ptr2){//swap the value between two pointer
        T temp = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = temp;
    }
   
    template<class T>
    T* last_element(T* array, int size){//return the last element of the array
        T* walker = array + (size -1);
        return walker;
    }

        template<class T>
    T* get_index(T* array, int index){//
        T* walker = array + index;
        return walker;
    }
}

const int MINIMUM_CAPACITY = 3;


//SIGNATURE

// string to_string(const string& item);
// string to_string(const char& item);

//=============================================
//Template Functions
template<class T>
void append(T* a, int& size, T value);                  //append value at the end of array,
                                                        //increment size by 1;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);            //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template<class T>
T* reallocate(T* a, int size, int capacity);            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template<class T>
void print_array(T* a, int size, 
            int capacity = 0, ostream& outs = cout);    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <class T>
void print(T* a, unsigned int how_many, 
                                ostream& outs = cout);  //print array

template<class T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find me' 
                                                        //return the first met entry
                                                        //if not found return nullptr

template <class T>
int search(T* a, int size, const T& find_me);           //search for 'find_me' 
                                                        //return the index of the first met entry
                                                        //if not found return -1

template <class T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos

template <class T>
void shift_left(T* a, int& size, T* shift_here);        //shift left @ pos: 
                                                        //    erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole

template <class T>
void shift_right(T *a, int &size, T* shift_here);       //shift right: 
                                                        //   make a hole

template<class T>
void copy_array(T *dest, const T* src, 
                                int many_to_copy);      //copy from src to dest

template <class T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

// template <class T>
// string array_string(const T *a, int size);              //return array 
//                                                         //  as a string



//=============================================
//DEFINITION//

template<class T>
void append(T* a, int& size, T value){
    T* last_element = a + size; 
    *last_element = value;
    size ++;
}

// void init_array(int* a, int size){
//     int* walker = a;
//     for(int i = 0; i < size; i++){
//     *walker++ = 0;
//     }
// }


template<class T>
T* allocate(int capacity){//FINISHED
    assert(capacity >= MINIMUM_CAPACITY && "The least capacity for allocating an array is 3");

    T* array = new T[capacity];
    return array;
}

template<class T>
T* reallocate(T* old_array, int size, int capacity ){//FINISHED
    T* new_array = allocate<T>(capacity);
   
    if(size > 0)
        copy_array(new_array, old_array, size);

    delete[] old_array;
    return new_array;
}

template<class T>
void print_array(T* a, int size, int capacity, ostream& outs){//FINISHED

    if(a == nullptr || size == 0){
        cout << "   NULL\n";
        return;
    }

    bool debug = false;

    if(capacity !=0)
        debug = true;
    // if(size > capacity){
    //     size = capacity;
    //     outs << "   [Exceeds Capacity] Size reduced to " << capacity << endl;
    // }

    T* walker = a;

    outs << "   (" << size;

    if(debug)
        outs << "/" << capacity;

    outs << ")  [     ";

    for(int i = 0; i < size; i++){
        outs << *walker++ << "     " ;
    }
    outs << "]" << endl;


    return;
}

template <class T>
void print(T* a, unsigned int how_many, ostream& outs){//FINISHED
  print_array(a,how_many,0,outs);
}

template<class T>
T* search_entry(T* a, int size, const T& find_me){//FINISHED
    T* walker = a;
    for(int i = 0; i < size; i++){
        if(*walker == find_me){
            return walker;
        }else walker ++;
    }
    
    return nullptr;
}

template <class T>
int search(T* a, int size, const T& find_me){//FINISHED
    T* result = search_entry(a, size, find_me);
    
    if(result == nullptr)
        return -1;
    else return (result - a);
}

template <class T>
void shift_left(T* a, int& size, T* shift_here){//FINISHED
    assert(size >= 1 && "Cannot shift_left for array with size smaller than 1");

    assert(((shift_here - a) < size && (shift_here - a) >= 0) && "Can only shift element within the array");

    
    assert(a != nullptr && "Array cannot be a nullptr");
     

    T* walker1 = shift_here;
    T* walker2 = shift_here+1;
    T* end_walker = a + size - 1;
    while(walker1 != end_walker){//swap the walker1 and walke2 vlaue, and then ++;
        helper::swap<T>(walker1++,walker2++);
    }

    //loop ends after walker1 is swaped when it is at a[size-1];
    size --;
    return;
}        

template <class T>
void shift_left(T* a, int& size, int shift_here){//FINISHED

    T* here = a + shift_here;

    shift_left(a,size,here);
    
    return;
}  

template <class T>
void shift_right(T *a, int &size, int shift_here){//FINISHED
    T* here = a + shift_here;

    shift_right(a,size,here);

    return;
}

template <class T>
void shift_right(T *a, int &size, T* shift_here){//FINISHED
    assert(size > 0 && "To shift an array, array Size must be greater than 0");

    assert(((shift_here - a) < size && (shift_here - a) >= 0) && "Can only shift element within the array");
    
    assert(a != nullptr && "Array cannot be a nullptr");
     

    T* hole = helper::last_element(a, size) + 1;
    *hole = *shift_here;
    T* walker = helper::last_element(a,size);

   while(walker != shift_here){
        helper::swap(walker--, hole--);
    }
    size++;
}

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy){
    assert((dest != nullptr && src != nullptr) && "Array src or dest cannot be nullptr");
    
    if(many_to_copy <= 0) return;
    assert(many_to_copy >= 1 && "Cannot copy less than 1 elements");

    T* walker_d = dest;
    const T* walker_s = src;

    for(int i = 0; i < many_to_copy; i++){
        *walker_d++ = *walker_s++;
    }
}

template <class T>
T* copy_array(const T *src, int size){
    assert(src != nullptr && "copy_array(): cannot copy from a nullptr, src");

    int capacity;
    if(size < MINIMUM_CAPACITY)
        capacity = 3;
        else capacity = size;
    
    T* new_array = allocate<T>(capacity);
    
    copy_array(new_array,src,size);

    return new_array;
}

// template <class T>
// string array_string(const T *a, int size){
//     string str;

//     if(size == 0)
//         str.append("[]");

//     for(int i = 0; i < size; i++){
//         str.append("[" + to_string(*a++) + "]");

//         if(i != size - 1){
//             str.append(" | ");
//         }
//     }


//     return str;
// }

// string to_string(const string& item){
//     return item;
// }

// string to_string(const char& item){
//     string temp = "";
//     temp += item;

//     return temp;
// }
#endif