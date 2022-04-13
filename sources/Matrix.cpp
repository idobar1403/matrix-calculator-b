#include "Matrix.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>
using namespace std;
size_t matrix_sum(const vector<vector<double>> &mat) // return sum of the matrix entries
{
    size_t sum = 0;
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat[0].size(); j++)
        {
            sum += mat[i][j];
        }
    }
    return sum;
}
int check_positive(int num)
{
    if (num < 0)
    {
        throw invalid_argument("can't have negative row or col");
    }
    return num;
}
namespace zich
{
    Matrix::Matrix(std::vector<double> vec, int rows, int columns) : Matrix(std::move(vec), static_cast<size_t>(check_positive(rows)), static_cast<size_t>(check_positive(columns))) {}
    Matrix::Matrix(std::vector<double> vec, size_t rows, size_t columns)
    {
        if (rows % 1 != 0 || columns % 1 != 0) // check for invalid input
        {
            throw invalid_argument("rows and columns must be int number");
        }
        if (rows * columns != vec.size()) // check for invalid input
        {
            throw invalid_argument("not enough size for matrix");
        }

        this->rows = rows;
        this->columns = columns;
        for (size_t i = 0; i < rows; i++)
        {
            Mat.push_back(vector<double>());
            for (size_t j = 0; j < columns; j++)
            {
                size_t index = (i * columns) + j;
                double num = vec[index];
                Mat.at(i).push_back(num);
            }
        }
    }
    bool Matrix::operator!=(const Matrix &other) const
    {
        if (this->rows != other.rows || this->columns != other.columns) // check for invalid input
        {
            throw invalid_argument("can't compare differet size matrix");
        }
        for (size_t i = 0; i < other.rows; i++)
        {
            for (size_t j = 0; j < other.columns; j++)
            {
                if (this->Mat.at(i).at(j) != other.Mat.at(i).at(j)) // check if there entry number that is not equal to his matched entry number
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Matrix::operator==(const Matrix &other) const
    {
        if (this->rows != other.rows || this->columns != other.columns) // check for invalid input
        {
            throw invalid_argument("can't compare differet size matrix");
        }
        for (size_t i = 0; i < other.rows; ++i)
        {
            for (size_t j = 0; j < other.columns; ++j)
            {
                if (this->Mat.at(i).at(j) != other.Mat.at(i).at(j)) // check that every entry number equals to his matched entry number
                {
                    return false;
                }
            }
        }
        return true;
    }
    Matrix &Matrix::operator*=(const Matrix &other)
    {
        if (this->columns != other.rows) // check for invalid input
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        *this = *this * other;
        return *this;
    }
    bool Matrix::operator<(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);

        return sum_self < sum_other; // check the sums
    }
    bool Matrix::operator<=(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        return sum_self <= sum_other; // check the sums
    }
    bool Matrix::operator>(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        return sum_self > sum_other; // check the sums
    }
    bool Matrix::operator>=(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        return sum_self >= sum_other; // check the sums
    }
    Matrix Matrix::operator*(const Matrix &other)
    {
        if (this->columns != other.rows) // check for invalid input
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<double> vec;
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < other.columns; j++) // iterate over the second matrix columns
            {
                size_t sum = 0;
                for (size_t k = 0; k < this->columns; k++)
                {
                    sum += this->Mat[i][k] * other.Mat[k][j]; // multiply every row entry with his matched column entry and sum this myltiplication
                }
                vec.push_back(sum);
            }
        }
        return Matrix{vec, this->rows, other.columns}; // return ans matrix with the ans vector
    }
    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->Mat.at(i).at(j)++; // increase by 1 every entry
            }
        }
        return *this;
    }
    Matrix Matrix::operator++(int postfix_increasment)
    {
        Matrix copy = *this;
        ++(*this);
        return copy;
    }
    Matrix &Matrix::operator--()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->Mat.at(i).at(j)--; // dicrease by 1 every entry
            }
        }
        return *this;
    }
    Matrix Matrix::operator--(int postfix_dicreasment)
    {
        Matrix copy = *this;
        --(*this);
        return copy;
    }
    Matrix Matrix::operator+()
    {
        vector<double> vec;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (Mat[i][j] < 0)
                {
                    vec.push_back(Mat[i][j] * (-1)); // if smaller than 0 then need to multiply by -1
                }
                else
                {
                    vec.push_back(Mat[i][j]); // create new matrix with the ans vector
                }
            }
        }
        return Matrix{vec, this->rows, this->columns};
    }
    Matrix Matrix::operator-()
    {
        vector<double> vec;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (Mat[i][j] > 0)
                {
                    vec.push_back(Mat[i][j] * (-1)); // if bigger than 0 then need to multiply by -1
                }
                else
                {
                    vec.push_back(Mat[i][j]);
                }
            }
        }
        return Matrix{vec, this->rows, this->columns}; // create new matrix with the ans vector
    }
    Matrix &Matrix::operator+=(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        *this = *this + other; // call the '+' function between two matrixes
        return *this;
    }
    Matrix Matrix::operator+(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<double> vec;
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                vec.push_back(Mat[i][j] + other.Mat[i][j]); // add every matching enteries and push the ans to the vector
            }
        }
        return Matrix{vec, this->rows, this->columns}; // create new matrix with the ans vector
    }
    Matrix Matrix::operator-(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<double> vec;
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                vec.push_back(Mat[i][j] - other.Mat[i][j]); // substruct every matching enteries and push the ans to the vector
            }
        }
        return Matrix{vec, this->rows, this->columns}; // create new matrix with the ans vector
        ;
    }
    Matrix &Matrix::operator-=(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows) // check for invalid input
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        *this = *this - other; // calling the '-' matrix function
        return *this;
    }
    Matrix Matrix::operator*(double scalar)
    {
        return scalar * (*this); // calling the other scalar multiplication function
    }
    Matrix operator*(double scalar, const Matrix &mat)
    {
        vector<double> vec;
        for (size_t i = 0; i < mat.rows; i++)
        {
            for (size_t j = 0; j < mat.columns; j++)
            {
                vec.push_back(mat.Mat[i][j] * scalar); // push the multiplication to the new matrix
            }
        }
        return Matrix{vec, mat.rows, mat.columns};
    }
    Matrix &Matrix::operator*=(double scalar)
    {
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                this->Mat[i][j] *= scalar; // simple number multiplication
            }
        }
        return *this;
    }
    ostream &operator<<(ostream &os, const Matrix &mat)
    {
        if (mat.Mat.empty() || mat.Mat[0].empty()) // check for invalid input
        {
            throw invalid_argument("no matrix to print");
        }
        for (size_t i = 0; i < mat.rows; i++)
        {
            os << "[";
            for (size_t j = 0; j < mat.columns; j++)
            {
                os << mat.Mat.at(i).at(j);
                if (j + 1 < mat.columns) // in order to not put space after the last digit
                {
                    os << " ";
                }
            }
            if (i + 1 < mat.rows) // in order to dont start new line at the end of the matrix
            {
                os << "]";
                os << "\n";
            }
            else
            {
                os << "]";
            }
        }
        return os;
    }
    istream &operator>>(istream &istr, Matrix &mat)
    {
        vector<double> vec;
        mat.Mat.clear(); // in order to make new matrix
        string str;
        size_t row = 0;
        size_t column = 0;
        for (char c = 0; istr.get(c) && c != '\n';) // read the string input
        {
            str += c;
        }
        row = (size_t)std::count(str.begin(), str.end(), '[');      // count the [ char in order to get number of rows
        if (row != (size_t)std::count(str.begin(), str.end(), ']')) // check for invalid input
        {
            throw std::out_of_range{"bad input!"};
        }
        for (size_t i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ') // count spaces inside [] to get the number of columns -1
            {
                column++;
            }
            if (str[i] == ']')
            {
                break;
            }
        }
        size_t sp = row * (column + 1) - 1;
        size_t p = row - 1;
        int space = 0;
        for (unsigned long i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ') // counting spaces to check for good input
            {
                sp--;
                space++;
            }
            if (str[i] == ',') // counting ',' to check for good input
            {
                p--;
                space = -1;
            }
            if (i != str.size() - 1 && str[i] == ']' && str[i + 1] != ',') // check for invalid input
            {
                throw std::out_of_range{"bad input!"};
            }
            if (str[i] == ']')
            {
                if (space != (column)) // check for invalid input
                {
                    throw std::out_of_range{"bad input!"};
                }
                space = 0;
            }
        }
        if (sp == 0)
        {
            // replace every '['  ']' with space for easier reading
            std::replace(str.begin(), str.end(), '[', ' ');
            std::replace(str.begin(), str.end(), ']', ' ');
        }
        else
        {
            throw std::out_of_range{"bad input!"};
        }
        if (p == 0)
        {
            // replace every ',' with space for easier reading
            std::replace(str.begin(), str.end(), ',', ' ');
        }
        else
        {
            throw std::out_of_range{"bad input!"};
        }

        for (size_t i = 0; i < str.size(); i++)
        {
            if (isdigit(str.at(i)) != 0) // read the string and find digits
            {
                string s;
                s += str.at(i);
                double num = stod(s);
                vec.push_back(num);
            }
        }
        Matrix mat1{vec, row, column + 1};
        mat = mat1;
        return istr;
    }
}
