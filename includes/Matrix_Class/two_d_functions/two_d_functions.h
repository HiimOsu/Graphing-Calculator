#ifndef MATRIX_TWO_D_FUNCTIONS_H
#define MATRIX_TWO_D_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

int array_size(int* sizes);
void print_array(int* a);
bool index_is_valid(int* sizes, int row, int col);


//To call: int** p = allocate_twod<int>(sizes_array)  

//allocate two d array, return the head of the twod_arr
//In this version, each arr is ended with an nullptr, indicating the end of the arr
template <class T>
T** allocate_twod(int* sizes); 
template <class T>
T** allocate_twod(int row, int cols);

//Deallocate the twod-arr
//Size = how many rows are in the twod
//Return nullptr
template <class T>
T** deallocate_twod(T** twod, int size);

//Read the value at [row][col]
template <class T>
T read_twod(T** twod, int row, int col);

template <class T>
void write_twod(T** twod, int row, int col, const T& item);

//Return the reference at[row][col]
template <class T>
T& get_twod(T** twod, int row, int col);

template<class T>
void init_twod(T** twod, int* sizes, T init_item);
template<class T>
void init_twod(T** twod, int row, int col, T init_item);

template<class T>
bool search_twod(T** twod, int* sizes, const T& key, int& row, int& col);

//return a pointer to the item if found, nullptr if not found: 
//                                                 (Ms. Barskhian)
template<class T> 
T* search_twod(T** twod, int* sizes, const T& key); 

template <class T>
ostream& print_twod(T** twod, int* sizes, ostream& outs = cout);


//===========================================================================

// ======================== Definition  =====================================




template <class T>
T** allocate_twod(int* sizes){ 
    assert(sizes != nullptr && 
    "ERROR [allocate_twod]: *sizes ptr cannot be NULL");
    
    
    int size = array_size(sizes);

    T** return_me = new T*[size + 1];
    T** walker = return_me;
    
    //allocate each row;
    for(int i = 0; i < size; i++){
        *walker = new T[sizes[i]];
        walker++;
    }
    
    //set the last row as NULLptr, the end of twod;
    *walker = nullptr;
    
    return return_me;
} 

template <class T>
T** allocate_twod(int rows, int cols){
    assert(rows != 0 && "rows cannot be 0");
    assert(cols != 0 && "cols cannot be 0");
    int arr[rows + 1];
    for(int i = 0; i < rows; i++){
        arr[i] = cols ;
    }
    arr[rows] = -1;
    // cout << "Debug: Creating 2dLength_arr: "; 
    // for(int i = 0; i < height+1; i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    return allocate_twod<T>(arr); 
}

template <class T>
T** deallocate_twod(T** twod, int size){
    if(*twod == nullptr || size <= 0)
        return twod;
    
    T** walker = twod;
    
    //allocate each row;
    for(int i = 0; i < size; i++){
        delete [] *walker;
        walker++; 
    }

    delete[] twod;

    twod = nullptr;

    return twod;
}

template <class T>
T read_twod(T** twod, int row, int col){
    assert(row >= 0 && col >= 0 && 
    "ERROR [read_twod]: row or col cannot be negative");
    
    //go to the destinated row
    T** walker_row = twod;
    walker_row = walker_row + row;

    //go to col
    T* walker_col = *walker_row;
    walker_col = walker_col + col;

    return *walker_col;
}

template <class T>
void write_twod(T** twod, int row, int col, const T& item){
    assert(row >= 0 && col >= 0 && 
    "ERROR [write_twod]: row or col cannot be negative");
    
    //go to the destinated row
    T** walker_row = twod;
    walker_row = walker_row + row;

    //go to col
    T* walker_col = *walker_row;
    walker_col = walker_col + col;

    *walker_col = item;     //Or we can just do: twod[row][col] = item;
}

template <class T>
T& get_twod(T** twod, int row, int col){
    assert(row >= 0 && col >= 0 && 
        "ERROR: [get_twod] row or col cannot be negative");
    
    
    return twod[row][col];
}

template<class T>
void init_twod(T** twod, int* sizes, T init_item){
    T** row_w = twod;
    T*  col_w;
    int row = 0;

    while(*row_w != nullptr){
        col_w = *row_w;
        for(int col = 0; col < sizes[row]; col++){
            *col_w++ = init_item;
        }
        row_w++;
        row++;
    }
}

template<class T>
void init_twod(T** twod, int row, int col, T init_item){
    int arr[row + 1];
    for(int i = 0; i < row; i++){
        arr[i] = col;
    }
    arr[row] = -1;

    init_twod<T>(twod, arr, init_item); 
}

template<class T>
bool search_twod(T** twod, int* sizes, const T& key, int& row, int& col){
    T** row_w = twod;
    T*  col_w;

    for(row = 0; row < array_size(sizes); row++){
        col_w = *row_w++;

        for(col = 0; col < sizes[row]; col++){
            if(*col_w++ == key){
                return true;
            }
        }
    }

    row = -1;
    col = -1;
    return false;
}

//return a pointer to the item if found, nullptr if not found: 
//                                                 (Ms. Barskhian)
template<class T> 
T* search_twod(T** twod, int* sizes, const T& key){
    int row, col;
    if(search_twod(twod, sizes, key, row, col) == true)
        return twod[row][col];
    else return nullptr;
}

template <class T>
ostream& print_twod(T** twod, int* sizes, ostream& outs){
    outs << endl;
    
    T** row_w = twod;
    T*  col_w;
    int row = 0;

    while(*row_w != nullptr){
        col_w = *row_w;

        outs << setw(15) << "(" << row << "|" <<  sizes[row] << ") "; 
        for(int col = 0; col < sizes[row]; col++){
            outs << "[" << *col_w++ << "] ";  
        }

        outs << endl;
        row_w++;
        row++;
    }
    
    
    return outs;
}

#endif