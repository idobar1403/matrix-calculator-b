#include "Matrix.hpp"
#include <stdexcept>
using namespace std;
size_t matrix_sum(const vector<vector<double>> &mat)
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
        if (rows % 1 != 0 || columns % 1 != 0)
        {
            throw invalid_argument("rows and columns must be int number");
        }
        if (rows * columns != vec.size())
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
    Matrix::Matrix(size_t rows, size_t columns)
    {
        if (rows < 0 || columns < 0)
        {
            throw invalid_argument("can't have negative row or col");
        }
        if (rows % 1 != 0 || columns % 1 != 0)
        {
            throw invalid_argument("rows and columns must be int number");
        }
        this->rows = rows;
        this->columns = columns;
        this->Mat.assign(rows, vector<double>(columns));
    }
    bool Matrix::operator!=(const Matrix &other) const
    {
        if (this->rows != other.rows || this->columns != other.columns)
        {
            throw invalid_argument("can't compare differet size matrix");
        }
        for (size_t i = 0; i < other.rows; i++)
        {
            for (size_t j = 0; j < other.columns; j++)
            {
                if (this->Mat.at(i).at(j) != other.Mat.at(i).at(j))
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Matrix::operator==(const Matrix &other) const
    {
        if (this->rows != other.rows || this->columns != other.columns)
        {
            throw invalid_argument("can't compare differet size matrix");
        }
        for (size_t i = 0; i < other.rows; ++i)
        {
            for (size_t j = 0; j < other.columns; ++j)
            {
                if (this->Mat.at(i).at(j) != other.Mat.at(i).at(j))
                {
                    return false;
                }
            }
        }
        return true;
    }
    Matrix Matrix::operator*=(const Matrix &other)
    {
        if (this->columns != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        // vector<vector<double>> mat(this->rows, vector<double>(other.columns));
        // for (size_t i = 0; i < this->rows; i++)
        // {
        //     for (size_t j = 0; j < other.columns; j++)
        //     {
        //         size_t sum = 0;
        //         for (size_t k = 0; k < this->columns; k++)
        //         {
        //             sum += this->Mat[i][k] * other.Mat[k][j];
        //         }
        //         mat[i][j] = sum;
        //     }
        // }
        // this->Mat.assign(this->rows, vector<double>(other.columns));
        // this->Mat.swap(mat);
        *this = *this * other;
        return *this;
    }
    bool Matrix::operator<(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self < sum_other)
        {
            return true;
        }

        return false;
    }
    bool Matrix::operator<=(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self <= sum_other)
        {
            return true;
        }
        return false;
    }
    bool Matrix::operator>(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self > sum_other)
        {
            return true;
        }
        return false;
    }
    bool Matrix::operator>=(const Matrix &other) const
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("two matrix has to be same size of columns an rows");
        }
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self >= sum_other)
        {
            return true;
        }

        return false;
    }
    Matrix Matrix::operator*(const Matrix &other)
    {
        if (this->columns != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<double>vec;
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < other.columns; j++)
            {
                size_t sum = 0;
                for (size_t k = 0; k < this->columns; k++)
                {
                    sum += this->Mat[i][k] * other.Mat[k][j];
                }
                vec.push_back(sum);
            }
        }
        return Matrix{vec, this->rows, other.columns};
    }
    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->Mat.at(i).at(j)++;
            }
        }
        return *this;
    }
    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment)
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
                this->Mat.at(i).at(j)--;
                ;
            }
        }
        return *this;
    }
    Matrix Matrix::operator--(int dummy_flag_for_postfix_increment)
    {
        Matrix copy = *this;
        --(*this);
        return copy;
    }
    Matrix Matrix::operator+()
    {
       vector<double>vec;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (Mat[i][j] < 0)
                {
                    vec.push_back(Mat[i][j] * (-1));
                }
                else
                {
                    vec.push_back(Mat[i][j]);
                }
            }
        }
        return Matrix{vec, this->rows, this->columns};
    }
    Matrix Matrix::operator-()
    {
        vector<double>vec;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (Mat[i][j] > 0)
                {
                    vec.push_back(Mat[i][j] * (-1));
                }
                else
                {
                    vec.push_back(Mat[i][j]);
                }
            }
        }
        return Matrix{vec, this->rows, this->columns};
    }
    Matrix Matrix::operator+=(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        // for (size_t i = 0; i < this->rows; i++)
        // {
        //     for (size_t j = 0; j < this->columns; j++)
        //     {
        //         Mat[i][j] += other.Mat[i][j];
        //     }
        // }
        *this = *this + other;
        return *this;
    }
    Matrix Matrix::operator+(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<double> vec;
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
               vec.push_back(Mat[i][j] + other.Mat[i][j]);
            }
        }
        return Matrix{vec, this->rows, this->columns};
    }
    Matrix Matrix::operator-(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<double> vec;
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                vec.push_back(Mat[i][j] - other.Mat[i][j]);
            }
        }
        return Matrix{vec, this->rows, this->columns};
        ;
    }
    Matrix Matrix::operator-=(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        // for (size_t i = 0; i < this->rows; i++)
        // {
        //     for (size_t j = 0; j < this->columns; j++)
        //     {
        //         Mat[i][j] -= other.Mat[i][j];
        //     }
        // }
        *this = *this - other;
        return *this;
    }
    Matrix Matrix::operator*(double scalar)
    {
        return scalar * (*this);
    }
    Matrix operator*(double scalar, const Matrix &mat)
    {
        vector<double> vec;
        for (size_t i = 0; i < mat.rows; i++)
        {
            for (size_t j = 0; j < mat.columns; j++)
            {
                vec.push_back(mat.Mat[i][j] * scalar);
            }
        }
        return Matrix{vec, mat.rows, mat.columns};
    }
    Matrix Matrix::operator*=(double scalar)
    {
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                this->Mat[i][j] *= scalar;
            }
        }
        return *this;
    }
    ostream &operator<<(ostream &os, const Matrix &mat)
    {
        if (mat.Mat.empty() || mat.Mat[0].empty())
        {
            throw invalid_argument("no matrix to print");
        }
        for (size_t i = 0; i < mat.rows; i++)
        {
            os<< "[";
            for (size_t j = 0; j < mat.columns; j++)
            {
                os<<mat.Mat.at(i).at(j);
                if (j + 1 < mat.columns)
                {
                    os<< " ";
                }
            }
            if (i + 1 < mat.rows)
            {
                os<< "]";
                os<< "\n";
            }
            else
            {
                os<< "]";
            }
        }
        return os;
    }
    istream &operator>>(istream &istr, Matrix &mat)
    {
        vector<double> vec;
        mat.Mat.clear();
        string str;
        double num = 0;
        istr.fill(' ');
        size_t row = 0;
        size_t column = 0;
        istr.get();
        bool open = false;
        int count1 = 0;
        int count2 = 0;
        bool start =true;
        for (char c = 0; istr.get(c) && c != '\n';)
        {
            if (c != '[' && start == true)
            {
                throw invalid_argument("bad input");
            }
            else if (c == '['&& open ==false)
            {
                column = 0;
                row++;
                open = true;
                count1=0;
                count2=0;
                start = false;
            }
            else if (c=='['&& open==true){
                throw invalid_argument("bad input");
            }
            else if ((c == ' ' || c == ']') && str.length() != 0 && open == true)
            {
                if(c==']'){
                    open = false;
                }
                num = stod(str);
                vec.push_back(num);
                column++;
                str = "";
                count1=0;
                count2=0;
            }
            else if (isdigit(c) != 0 || (str.length()!=0 && c=='.'))
            {
                str += c;
                count1=0;
                count2=0;
            }
            else if (c==']' && open == false)
            {
                throw invalid_argument("bad input");
            }
            
            else if(c==',' && start == false)
            {
                count1++;
                if(count1>1){
                throw invalid_argument("bad input");
                }
            }
            
            
            else if(c==' '){
                count2++;
                if(count2>1){
                throw invalid_argument("bad input");
                }
            }
            
        }
        Matrix m{vec, row, column};
        mat = m;
        return istr;
    }
}
