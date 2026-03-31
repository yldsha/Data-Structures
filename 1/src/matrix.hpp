#pragma once

class Matrix
{
private:
    int rows;
    int cols;
    double **data;

public:
    Matrix(int n);
    Matrix(int n, int m, double fillValue = 0);
    Matrix(const Matrix &other);

    ~Matrix();

    double get(int i, int j) const;
    int getHeight() const;
    int getWidth() const;

    void set(int i, int j, double value);

    void negate();
    void addInPlace(Matrix &other);
    Matrix multiply(Matrix &other);

    void printMatrix();

    Matrix &operator=(const Matrix &a);
    Matrix &operator+=(const Matrix &a);
    Matrix &operator-=(const Matrix &a);
    Matrix &operator*=(double a);
    Matrix &operator/=(double a);
    Matrix operator+(const Matrix &a) const;
    Matrix operator-(const Matrix &a) const;
    Matrix operator*(const Matrix &a) const;
    Matrix operator*(double a) const;
    Matrix operator/(double a) const;
    
};

Matrix operator*(double a, const Matrix& b);
Matrix operator-(const Matrix& a);
