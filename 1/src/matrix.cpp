#include "matrix.hpp"
#include <iostream>

Matrix::Matrix(int n) : Matrix(n, n)
{

    for (int i = 0; i < rows && i < cols; i++)
    {
        data[i][i] = 1.0;
    }
};

Matrix::Matrix(int n, int m, double fillValue)
    : rows(n), cols(m)
{
    if (cols <= 0 || rows <= 0)
    {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }

    data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = fillValue;
        }
    }
}

Matrix::Matrix(const Matrix &other)
    : rows(other.rows), cols(other.cols)
{
    data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix()
{

    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

double Matrix::get(int i, int j) const { return data[i][j]; }
int Matrix::getHeight() const { return rows; }
int Matrix::getWidth() const { return cols; }

void Matrix::set(int i, int j, double value)
{
    data[i][j] = value;
}

void Matrix::negate()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = data[i][j] * (-1);
        }
    }
}

void Matrix::addInPlace(Matrix &other)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = data[i][j] + other.data[i][j];
        }
    }
}

Matrix Matrix::multiply(Matrix &other)
{
    if (cols != other.rows)
    {
        throw std::invalid_argument(
            "Число столбцов первой матрицы не равно числу строк второй матрицы");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

void Matrix::printMatrix()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Matrix &Matrix::operator=(const Matrix &a)
{
    if (this == &a)
    {
        return *this;
    }
    cols = a.cols;
    rows = a.rows;
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
    data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[cols];
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = a.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix &a)
{
    if (rows != a.rows || cols != a.cols){
        throw std::invalid_argument("Размеры матриц должны совпадать");
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] += a.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix &a)
{
    if (rows != a.rows || cols != a.cols){
        throw std::invalid_argument("Размеры матриц должны совпадать");
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] -= a.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(double a)
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] *= a;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(double a)
{
    if (a == 0){
        throw std::invalid_argument("Деление на ноль");
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] /= a;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &a) const
{
    if (rows != a.rows || cols != a.cols){
        throw std::invalid_argument("Размеры матриц должны совпадать");
    }
    Matrix result(*this);
    result += a;
    return result;
}
Matrix Matrix::operator-(const Matrix &a) const
{
    if (rows != a.rows || cols != a.cols){
        throw std::invalid_argument("Размеры матриц должны совпадать");
    }
    Matrix result(*this);
    result -= a;
    return result;
}
Matrix Matrix::operator*(const Matrix &a) const
{
    if (cols != a.rows){
        throw std::invalid_argument("Кол-во строк первой матрицы должно сооответствовать кол-ву столбцов второй");
    }
    Matrix result(rows, a.cols, 0.0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result.data[i][j] += data[i][k] * a.data[k][j];
            }
        }
    }
    return result;
}
Matrix Matrix::operator*(double a) const
{
    Matrix result(*this);
    result *= a;
    return result;
}
Matrix Matrix::operator/(double a) const
{
    if (a == 0){
        throw std::invalid_argument("Деление на ноль");
    }
    Matrix result(*this);
    result /= a;
    return result;
}

Matrix operator*(double a, const Matrix& b)
{
    return b * a;
}
Matrix operator-(const Matrix& a)
{
    Matrix result(a);
    result *= -1;
    return result;
}
