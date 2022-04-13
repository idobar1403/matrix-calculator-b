#ifndef Matrix_h
#define Matrix_h
#include <vector>
#include <iostream>
namespace zich
{
    class Matrix
    {
    private:
        size_t rows;
        size_t columns;
        std::vector<std::vector<double>> Mat;

    public:
        Matrix(std::vector<double> vec, int rows, int columns);
        Matrix(std::vector<double> vec, size_t rows, size_t columns);
        Matrix(size_t rows, size_t columns);
        // function for matrix equalization
        bool operator!=(const Matrix &other) const;
        bool operator==(const Matrix &other) const;
        bool operator<=(const Matrix &other) const;
        bool operator<(const Matrix &other) const;
        bool operator>=(const Matrix &other) const;
        bool operator>(const Matrix &other) const;
        // mathematical functions between two matrix
        Matrix operator+(const Matrix &other);
        Matrix& operator+=(const Matrix &other);
        Matrix operator-(const Matrix &other);
        Matrix& operator-=(const Matrix &other);
        Matrix operator*(const Matrix &other);
        Matrix& operator*=(const Matrix &other);
        // mathematical functions on matrix
        friend Matrix operator*(double scalar, const Matrix &mat);
        Matrix operator*(double scalar);
        Matrix& operator*=(double scalar);
        Matrix& operator++();
        Matrix operator++(int postfix_increasment);
        Matrix& operator--();
        Matrix operator--(int postfix_dicreasment);
        Matrix operator+();
        Matrix operator-();
        friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
        friend std::istream &operator>>(std::istream &istr, Matrix &mat);
    };
}
#endif