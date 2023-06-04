#ifndef MATRIX_H
#define MATRIX_H
#include "iostream"
#include <cassert>
#include "../two_d_functions/two_d_functions.h"

using namespace std;

template <class T>
class Matrix
{
public:
    //Constructor
    Matrix(int rows, int cols, const T = T());

    //Big3
    Matrix& operator=(const Matrix& copy_me);
    Matrix(const Matrix& copy_me);
    ~Matrix();

    //Negate the matrixies
    template<class U>
    friend Matrix<U> operator-(const Matrix<U>& m1);
    
    template<class U>
    friend Matrix<U> pow(const Matrix<U>& m1, const int pow);
    
    template<class U>
    friend Matrix<U> operator*(const Matrix<U>&  m1, const Matrix<U>& m2);

    template<class U>
    friend Matrix<U> operator*(const U& scaler ,const Matrix<U>&  m1);

    template<class U>
    friend Matrix<U> operator+(const Matrix<U>&  m1, const Matrix<U>& m2);

    template<class U>
    friend Matrix<U> operator-(const Matrix<U>&  m1, const Matrix<U>& m2);

    Matrix<T>& operator+=(const Matrix& m1);
    Matrix<T>& operator-=(const Matrix& m1);
    Matrix<T>& operator*=(const Matrix& m1);

    T*  operator[](int rows);
    const T* operator[](int rows) const;

    T& at(int rows, int cols);
    const T* at(int rows, int cols) const;
    
    int rows() const
    {return _rows;} 
    int cols() const 
    {return _cols;} 

    void Print(){
        for(int j = 0; j < _rows; j++){
            for(int i = 0; i < _cols; i++){
                cout << "["<<_arr[j][i] << "] ";    
            }
            cout << endl;
        }
    
    }

private:
    T** _arr;
    int _rows, _cols;
};


//****************************************************
        //Constructors && Big3
//----------------------------------------------------


template <class T>
Matrix<T>::Matrix(int rows, int cols, const T item)
{
    _rows = rows;
    _cols = cols;
    assert(rows >= 1 && cols >= 1 && "Matri: [Constructor Error], ");
    _arr = allocate_twod<T>(rows, cols);
    init_twod<T>(_arr, rows, cols, item);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& copy_me){
    if(this == &copy_me){
        return *this;
    }
    if(_rows != copy_me._rows || _cols != copy_me._cols){
        if(_arr != nullptr){
            deallocate_twod<T>(_arr, _rows);
        }
        _rows = copy_me._rows;
        _cols = copy_me._cols;
        _arr = allocate_twod<T>(_rows, _cols);
    }

    for(int j = 0; j < _rows; j++){
        for(int i = 0; i < _cols; i++){
            _arr[j][i] = copy_me._arr[j][i];
        }
    }
    
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& copy_me){
    _rows = copy_me._rows;
    _cols = copy_me._cols;
    _arr = allocate_twod<T>(_rows, _cols);

    for(int j = 0; j < _rows; j++){
        for(int i = 0; i < _cols; i++){
            _arr[j][i] = copy_me._arr[j][i];
        }
    }
    
    // cout << "Copied MATRIX:" << endl;
    // for(int j = 1; j <= _rows; j++){
    //     for(int i = 1; i <=_cols; i++){
    //     cout << "[" << _arr[j][i] << "] ";
    //     }
    //     cout << endl;
    // }
    // cout << "Leaving Copy Construtor!" << endl;
}


template <class T>
Matrix<T>::~Matrix<T>(){
    deallocate_twod<T>(_arr, _rows);
}

//****************************************************
       
        //Unary Operaotr

//----------------------------------------------------

template <class T>
Matrix<T> operator-(const Matrix<T>& m1) {
    Matrix<T> m0 = m1;
    for(int j = 1; j <= m0._rows; j++){
        for(int i = 1; i <= m0._cols; i++){
            m0[j][i] = -(m0[j][i]);
        }
    }
    return  m0;
}
//****************************************************
       
        //Matrix Arithemtic && Mutiplication

//----------------------------------------------------

template <class T>
Matrix<T> pow(const Matrix<T>& m1, const int pow){
    Matrix<T> result = m1;
    for(int i = 1; i < pow; i++){
        result = (result * m1);
    }

    return result;
}


template <class T>
Matrix<T> operator*(const Matrix<T>&  m1, const Matrix<T>& m2){
    assert(m1._cols == m2._rows && "Matrix: [Mutiplication Error], m1 Cols must =  m2 Rows");
    Matrix<T> m0(m1._rows, m2._cols);
    for(int j =  1; j <= m0._rows; j++){
        for(int i = 1; i <= m0._cols; i++){
            for(int k = 1; k <= m2._rows; k++){
                 m0[j][i] += m2[k][i] * m1[j][k];
            }
            
        }
    }
    return m0;
}

template <class T>
Matrix<T> operator*(const T& scaler, const Matrix<T>&  m1){
    // cout << "Entering scaler X Matrix!" << endl; 
    Matrix<T> m0(m1._rows, m1._cols);
    for(int j = 1; j <= m1._rows; j++){
        for(int i = 1; i <= m1._cols; i++){
            m0[j][i] = m1[j][i] * scaler;
        }
    }

    // cout << "Leaving Scaler X Matrix!" << endl;
    return m0;
}


template <class T>
Matrix<T> operator+(const Matrix<T>&  m1, const Matrix<T>& m2){
    assert(m1._cols == m2._cols && "Matrix: [Addition Error], Cols must be  in the same size" );
    assert(m1._rows == m2._rows && "Matrix: [Addition Error], Rows must be in the same size" );
    
    Matrix<T> m0(m1._rows, m1._cols);

    for(int j = 1; j <= m1._rows; j++){
        for(int i = 1; i <= m1._cols; i++){
            m0[j][i] = m1[j][i] + m2[j][i];
        }
    }
    return m0;
}

template <class T>
Matrix<T> operator-(const Matrix<T>&  m1, const Matrix<T>& m2){
    return (m1) + (-m2);
}



template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m1){
    *this = *this + m1;
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m1){
    *this = *this - m1;
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m1){
    *this =  *this * m1;
    return *this;
}


//****************************************************
    //Accessor Functions
//----------------------------------------------------

template <class T>
T*  Matrix<T>::operator[](int rows){
    assert( rows > 0 && _rows >= rows && "Matrix: [Index Error] , index is out of bound");
    return (_arr[rows-1])-1;
}

template <class T>
const T* Matrix<T>::operator[](int rows) const{
    assert( rows > 0 && _rows >= rows && "Matrix: [Index Error] , index is out of bound");
    return (_arr[rows -1])-1;
}

template <class T>
T& Matrix<T>::at(int rows, int cols){
    assert( rows > 0 && _rows >= rows && "Matrix: [Index Error] , index is out of bound");
    assert( cols > 0 && _cols >= cols && "Matrix: [Index Error] , index is out of bound");
    return _arr[rows -1][cols-1];
}
template <class T>
const T* Matrix<T>::at(int rows, int cols) const{
    assert( rows > 0 && _rows >= rows && "Matrix: [Index Error] , index is out of bound");
    assert( cols > 0 && _cols >= cols && "Matrix: [Index Error] , index is out of bound");
    return _arr[rows -1][cols-1];
}



#endif