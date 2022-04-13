#include "sources/Matrix.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace zich;
using namespace std;
int main()
{
    cout << "Rules:" << endl;
    cout << "1.Create vector of numbers (every row must contain the same amount of numbers)."
         << "\n";
    cout << "2.Choose size of the vector by setting rows and columns, must be -> rows * columns = vector.length."
         << "\n";
    cout << "3.In order to do math functions between matrixes you must make another matrix with the same rules as above."
         << "\n";
    cout << "4.In order to do math functions between your matrix and scalar, you must set value for scalar."
         << "\n";
    cout << "5.You can also do functions on the math itself."
         << "\n";
    cout << "For functions between matrixes 1."
         << "\n";
    cout << "For functions with scalar choose 2."
         << "\n";
    cout << "For functions on the matrix itself choose 3."
         << "\n";
    cout << "To exit choose any other button."
         << "\n";
    cout << "Your choose: ";
    int num;
    try
    {
        cin >> num;
    }
    catch (exception &e)
    {
        cout << "You choose to exit, bye.\n";
        return 0;
    }
    try
    {
        cout << "First let's create matrix.\n";
        cout << "Enter string.\n";
        cout << "Every row must be inside [ and ] like this [1 2 3] and be seperated by ', ' like this [1], [2].\n ";
        cout << "Every two number in string must be seperated by space.\n";
        cout << "Enter your string:";
        string str;
        fflush(stdin);
        std::getline(cin >> ws, str);
        str += '\n';
        cout << str;
        istringstream s{str};
        cout << "Now enter matching rows and columns size.\n";
        size_t rows, columns;
        cout << "Rows: ";
        cin >> rows;
        cout << "Columns: ";
        cin >> columns;
        vector<double> vec(rows * columns);
        cout << "building mat: \n";
        Matrix mat{vec, rows, columns};
        s >> mat;
        cout << mat << endl;
        if (num == 1)
        {
            cout << "Create the second matrix.\n";
            cout << "In order to multiply the size of columns of the first matrix must be equal to the size of rows of this matrix.\n";
            cout << "In order to do the other function size must be the same\n";
            cout << "Enter string.\n";
            cout << "Every row must be inside [ and ] like this [1 2 3] and be seperated by ', ' like this [1], [2].\n ";
            cout << "Every two number in string must be seperated by space.\n";
            string str1;
            cout << "Enter your string: ";
            fflush(stdin);
            std::getline(cin >> ws, str1);
            str1 += '\n';
            istringstream s1{str1};
            cout << "Now enter matching rows and columns size.\n";
            size_t rows_other;
            cout << "Rows: ";
            cin >> rows_other;
            size_t columns_other;
            cout << "Columns: ";
            cin >> columns_other;
            vector<double> vec_other(rows_other * columns_other);
            Matrix mat_other{vec_other, rows_other, columns_other};
            s1 >> mat_other;
            cout << mat_other << endl;
            cout << "Choose 1 to * , 2 to *=, 3 to ==, 4 to !=, 5 to >, 6 to >=, 7 to <, 8 to <=,\n";
            cout << "9 to +, 10 to +=, 11 to -, 12 to -=, 13 to create new matrix.\n";
            int ans;
            cout << "Your choice:";
            cin >> ans;

            while (1 <= ans && ans <= 13)
            {
                if (ans == 1)
                {
                    cout << (mat * mat_other);
                }
                else if (ans == 2)
                {
                    mat *= mat_other;
                    cout << mat;
                }
                else if (ans == 3)
                {
                    if (mat == mat_other)
                    {
                        cout << "true";
                    }
                    else
                    {
                        cout << "false";
                    }
                }
                else if (ans == 4)
                {
                    if (mat != mat_other)
                    {
                        cout << "true";
                    }
                    else
                    {
                        cout << "false";
                    }
                }
                else if (ans == 5)
                {
                    if (mat > mat_other)
                    {
                        cout << "true";
                    }
                    else
                    {
                        cout << "false";
                    }
                }
                else if (ans == 6)
                {
                    if (mat >= mat_other)
                    {
                        cout << "true";
                    }
                    else
                    {
                        cout << "false";
                    }
                }
                else if (ans == 7)
                {
                    if (mat < mat_other)
                    {
                        cout << "true";
                    }
                    else
                    {
                        cout << "false";
                    }
                }
                else if (ans == 8)
                {
                    if (mat <= mat_other)
                    {
                        cout << "true";
                    }
                    else
                    {
                        cout << "false";
                    }
                }
                else if (ans == 9)
                {
                    cout << (mat + mat_other);
                }
                else if (ans == 10)
                {
                    mat += mat_other;
                    cout << mat;
                }
                else if (ans == 11)
                {
                    cout << (mat - mat_other);
                }
                else if (ans == 12)
                {
                    mat -= mat_other;
                    cout << mat;
                }
                else
                {
                    string str1;
                    cout << "Enter your string: ";
                    fflush(stdin);
                    std::getline(cin >> ws, str1);
                    str1 += '\n';
                    istringstream s1{str1};
                    cout << "Now enter matching rows and columns size.\n";
                    size_t rows_other;
                    cout << "Rows: ";
                    cin >> rows_other;
                    size_t columns_other;
                    cout << "\nColumns: ";
                    cin >> columns_other;
                    vector<double> vec_other(rows_other * columns_other);
                    Matrix mat_other{vec_other, rows_other, columns_other};
                    s1 >> mat_other;
                    cout << mat_other;
                }
                cout << "\n";
                cout << "Choose 1 to * , 2 to *=, 3 to ==, 4 to !=, 5 to >, 6 to >=, 7 to <, 8 to <=,\n";
                cout << "9 to +, 10 to +=, 11 to -, 12 to -=, 13 to create new matrix.\n";
                cout << "Your choice:";
                cin >> ans;
                cout << endl;
            }
        }
        else if (num == 2)
        {
            cout << "choose scalar";
            double scalar;
            cin >> scalar;
            cout << "For * choose 1, for *= choose 2, for new scalar choose 3\n";
            int ans2;
            cin >> ans2;
            cout << endl;
            while (ans2 == 1 || ans2 == 2 || ans2 == 3)
            {
                if (ans2 == 1)
                {
                    cout << scalar * mat;
                }
                else if (ans2 == 2)
                {
                    mat *= scalar;
                    cout << mat;
                }
                else
                {
                    cout << "choose scalar";
                    cin >> scalar;
                }
                cout << "For * choose 1, for *= choose 2, for new scalar choose 3\n";
                cin >> ans2;
                cout << endl;
            }
        }
        else if (num == 3)
        {
            cout << "For ++ choose 1, for -- choose 2, for + choose 3, for + choose 4\n";
            int ans3;
            cin >> ans3;
            while (ans3 >= 1 && ans3 <= 4)
            {
                if (ans3 == 1)
                {
                    cout << mat++;
                }
                else if (ans3 == 2)
                {
                    cout << mat--;
                }
                else if (ans3 == 3)
                {
                    cout << (+mat);
                }
                else
                {
                    cout << (-mat);
                }
                cout << endl;
                cout << "For ++ choose 1, for -- choose 2, for + choose 3, for + choose 4\n";
                cin >> ans3;
                cout << endl;
            }
        }
        else
        {
            cout << "Ending program, bye\n";
            return 1;
        }
        cout << "Ending program, bye\n";
        return 1;
    }
    catch (exception &e)
    {
        cout << "error happend, bye.\n";
        return 0;
    }
}