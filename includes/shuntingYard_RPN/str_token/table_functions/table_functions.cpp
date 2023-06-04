#include "table_functions.h"

void init_table(int table[][MAX_COL], int num_state, int num_input){
    assert(num_input <= MAX_COL && num_state <= MAX_ROW);
    for(int row = 0; row < num_state; row++){
        for(int col = 0; col < num_input; col++){
            if(col == 0)
                table[row][col] = 0;
            else table[row][col] = -1;
        }
    }

}
void mark_success(int table[][MAX_COL],int state){
     assert(state < MAX_ROW);
   
    table[state][0] = 1;
}
void mark_fail(int table[][MAX_COL],int state){
    assert(state < MAX_ROW);
    table[state][0] = 0;
}
void mark_des(int table[][MAX_COL], int state, int input, int des){
    assert(input != 0);
    assert(state < MAX_ROW && input < MAX_COL && des  < MAX_ROW);
    table[state][input] = des;
}

int get_des(const int table[][MAX_COL], int state, int input){
    return table[state][input];
}
bool get_suc_fail(const int table[][MAX_COL], int state){
    if(state == -1)
        return false;
    return table[state][0];
}

void print_table(int table[][MAX_COL], int num_row, int num_col){

    for(int i = -1; i < num_row; i++){
        std::cout << std::endl;
        if(i == -1)
            cout << "[    ]    ";
        else cout << '[' << setw(4) <<  i << "]    ";

        for(int j = 0; j < num_col; j++){
            
            if(i != -1){
                if(j == 0){
                    cout << table[i][j] << "  |";
                }else cout << setw(4) << table[i][j];
            }else{
                if(j == 0){
                    cout << "T/F|";
                }else  cout << setw(2) << "[" << j << "]";
            }

        }
    }
}