#include "matrix.hpp"
#include <iostream>

int main() {
    // Тест 1: Единичная матрица
    Matrix m1(3);
    std::cout << "Единичная матрица 3x3:" << std::endl;
    m1.printMatrix();
    std::cout << std::endl;

    // Тест 2: Матрица с заполнением и копирование
    Matrix filled(2, 2, 9);
    Matrix copy(filled);
    std::cout << "Оригинал:" << std::endl;
    filled.printMatrix();
    std::cout << "Копия:" << std::endl;
    copy.printMatrix();
    std::cout << std::endl;

    // Тест 3: Умножение матриц
    Matrix A(2, 3);
    A.set(0, 0, 1); A.set(0, 1, 2); A.set(0, 2, 3);
    A.set(1, 0, 4); A.set(1, 1, 5); A.set(1, 2, 6);
    
    Matrix B(3, 2);
    B.set(0, 0, 7); B.set(0, 1, 8);
    B.set(1, 0, 9); B.set(1, 1, 10);
    B.set(2, 0, 11); B.set(2, 1, 12);

    std::cout << "A * B =" << std::endl;
    Matrix C = A.multiply(B);
    C.printMatrix();

    return 0;
}


