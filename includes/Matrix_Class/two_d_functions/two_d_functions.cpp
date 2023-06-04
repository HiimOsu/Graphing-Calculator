#include "two_d_functions.h"


int array_size(int* sizes){
    int count = 0;      //count how many array
    int* walker = sizes;

    while(*walker != -1){
        walker ++;
        count ++;
    }
    
    return count;
}

void print_array(int* a){
    int* walker = a;

    while(*walker != -1){
        cout << endl;
        for(int i = 0; i < *walker; i++){
            cout << "[0] ";
        }
        walker++;
    }
}

bool index_is_valid(int* sizes, int row, int col){
    if(col < 0 || row < 0)
        return false;
    
    //check row is valid
    if(row > array_size(sizes) - 1)
        return false;

    //check col is valid
    int* walker = sizes + row;
    if(col > *walker -1)
        return false;
    
    return true;
}