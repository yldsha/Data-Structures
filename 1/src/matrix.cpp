#include "matrix.hpp"
#include <iostream>


Matrix::Matrix(int n): Matrix(n,n){
   
    for (int i = 0; i < rows && i < cols; i++) {
        data[i][i] = 1.0;
    }
};

Matrix::Matrix(int n, int m, double fillValue)
:rows(n), cols(m){
    if(cols <= 0 || rows <= 0){
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }

    data = new double* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = fillValue;
        }
    }
}

Matrix::Matrix(const Matrix& other)
: rows(other.rows), cols(other.cols){
    data = new double* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix(){
    
        for (int i = 0; i < rows; i++){
            delete[] data[i];
        }
        delete[] data;
    
}

double Matrix::get(int i, int j) const {return data[i][j];}
int Matrix::getHeight() const {return rows;}
int Matrix::getWidth() const {return cols;}

void Matrix::set(int i, int j, double value){
    data[i][j] = value;
}

void Matrix::negate(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = data[i][j] * (-1);
        }
    }
}

void Matrix::addInPlace(Matrix &other){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = data[i][j] + other.data[i][j];
        }
    }
}

Matrix Matrix::multiply(Matrix &other){
    if (cols != other.rows){
        throw std::invalid_argument(
            "Число столбцов первой матрицы не равно числу строк второй матрицы"
        );
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < other.cols; j++){
            for (int k = 0; k < cols; k++){
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

void Matrix::printMatrix(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout<<data[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}
