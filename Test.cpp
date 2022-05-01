#include "doctest.h"
#include "Matrix.hpp"
#include <sstream>
using namespace zich;
#include <iostream>
#include <string>
using namespace std;
TEST_CASE("Constructor check")
{
    std::vector<double> another_mat = {21, 34, 11, 57, 42, 0, 55, 12, 6, 12, 56, 8, 23, 78, 9, 13, 41, 5};

    CHECK_NOTHROW(Matrix(another_mat, 6, 3));
}
TEST_CASE("Matrix multiplication")
{
    stringstream s;
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix ident{identity, 3, 3};
    Matrix a{identity, 3, 3};
    s << (a * ident);
    CHECK(s.str() == "[ 1 0 0 ]\n"
                     "[ 0 1 0 ]\n"
                     "[ 0 0 1 ]\n");
    s.str("");
    std::vector<double> identity_2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
    std::vector<double> inverse_ident_2 = {0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5};
    Matrix ident_2{identity_2, 3, 3};
    Matrix ident_2_invers{inverse_ident_2, 3, 3};
    s << (ident_2 * ident_2_invers); // check that it gives the identity matrix from both sides
    CHECK(s.str() == "[ 1 0 0 ]\n"
                     "[ 0 1 0 ]\n"
                     "[ 0 0 1 ]\n");
    s.str("");
    s << (ident_2_invers * ident_2); // check that it gives the identity matrix from both sides
    CHECK(s.str() == "[ 1 0 0 ]\n"
                     "[ 0 1 0 ]\n"
                     "[ 0 0 1 ]\n");
    std::vector<double> big_mat = {1, 2, 3, 45, 78, 4, 4, 5, 6, 97, 66, -9, 16, 1, 3, 22, 44, 12, 33, 41, 0, -9, 14, 12, 10, 8, 23, -9, -2, 11};
    std::vector<double> another_mat = {21, 34, 11, 57, 42, 0, 55, 12, 6, 12, 56, 8, 23, 78, 9, 13, 41, 5};
    Matrix big{big_mat, 5, 6};
    Matrix same_row_size{another_mat, 6, 3};
    s.str("");
    s << (big * same_row_size); // big matrix multiplication check
    CHECK(s.str() == "[ 2686 8922 1111 ]\n"
                     "[ 3264 10629 1405 ]\n"
                     "[ 1990 5778 826 ]\n"
                     "[ 3400 3924 477 ]\n"
                     "[ 1920 743 213 ]\n");
    s.str("");
    big *= same_row_size;
    s << (+big); // big matrix multiplication check
    CHECK(s.str() == "[ 2686 8922 1111 ]\n"
                     "[ 3264 10629 1405 ]\n"
                     "[ 1990 5778 826 ]\n"
                     "[ 3400 3924 477 ]\n"
                     "[ 1920 743 213 ]\n");
}
TEST_CASE("Matrix plus minus")
{
    std::vector<double> identity_to_be = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<double> make_identity = {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0};
    stringstream s;
    Matrix iden{identity_to_be, 4, 4};
    Matrix minus_iden{make_identity, 4, 4};
    s << (iden - minus_iden); // want the identity matrix
    CHECK(s.str() == "[ 1 0 0 0 ]\n"
                     "[ 0 1 0 0 ]\n"
                     "[ 0 0 1 0 ]\n"
                     "[ 0 0 0 1 ]\n");
    s.str("");
    s << (minus_iden - iden); // want the minus identity matrix
    CHECK(s.str() == "[ -1 0 0 0 ]\n"
                     "[ 0 -1 0 0 ]\n"
                     "[ 0 0 -1 0 ]\n"
                     "[ 0 0 0 -1 ]\n");
    s.str("");
    s << (minus_iden + iden);
    CHECK(s.str() == "[ 1 2 2 2 ]\n"
                     "[ 2 1 2 2 ]\n"
                     "[ 2 2 1 2 ]\n"
                     "[ 2 2 2 1 ]\n");
    std::vector<double> minus_make_identity = {0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0};
    Matrix minus_make_iden{minus_make_identity, 4, 4};
    s.str("");
    s << (minus_iden + minus_make_iden); // want zero matrix
    CHECK(s.str() == "[ 0 0 0 0 ]\n"
                     "[ 0 0 0 0 ]\n"
                     "[ 0 0 0 0 ]\n"
                     "[ 0 0 0 0 ]\n");
    s.str("");
    s << (minus_iden - minus_make_iden); // every entry 2 except the identity entries
    CHECK(s.str() == "[ 0 2 2 2 ]\n"
                     "[ 2 0 2 2 ]\n"
                     "[ 2 2 0 2 ]\n"
                     "[ 2 2 2 0 ]\n");
    s.str("");
    s << (iden + minus_make_iden); // want the identity matrix
    CHECK(s.str() == "[ 1 0 0 0 ]\n"
                     "[ 0 1 0 0 ]\n"
                     "[ 0 0 1 0 ]\n"
                     "[ 0 0 0 1 ]\n");
    s.str("");
    s << (iden - minus_make_iden);
    CHECK(s.str() == "[ 1 2 2 2 ]\n"
                     "[ 2 1 2 2 ]\n"
                     "[ 2 2 1 2 ]\n"
                     "[ 2 2 2 1 ]\n");
    s.str("");
    iden += minus_make_iden;
    s << (+iden); // want the identity matrix
    CHECK(s.str() == "[ 1 0 0 0 ]\n"
                     "[ 0 1 0 0 ]\n"
                     "[ 0 0 1 0 ]\n"
                     "[ 0 0 0 1 ]\n");
    std::vector<double> big_mat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::vector<double> another_big_mat = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    Matrix big_m{big_mat, 4, 4};
    Matrix a_m{another_big_mat, 4, 4};
    s.str("");
    s << (big_m - a_m); // minus 1 at every entry
    CHECK(s.str() == "[ -1 -1 -1 -1 ]\n"
                     "[ -1 -1 -1 -1 ]\n"
                     "[ -1 -1 -1 -1 ]\n"
                     "[ -1 -1 -1 -1 ]\n");
    s.str("");
    s << (+(big_m - a_m)); // 1 at every entry
    CHECK(s.str() == "[ 1 1 1 1 ]\n"
                     "[ 1 1 1 1 ]\n"
                     "[ 1 1 1 1 ]\n"
                     "[ 1 1 1 1 ]\n");
    s.str("");
    s << (-(a_m - big_m)); // minus 1 at every entry
    CHECK(s.str() == "[ -1 -1 -1 -1 ]\n"
                     "[ -1 -1 -1 -1 ]\n"
                     "[ -1 -1 -1 -1 ]\n"
                     "[ -1 -1 -1 -1 ]\n");
    s.str("");
    big_m -= a_m;
    s << (+(big_m)); // 1 at every entry
    CHECK(s.str() == "[ 1 1 1 1 ]\n"
                     "[ 1 1 1 1 ]\n"
                     "[ 1 1 1 1 ]\n"
                     "[ 1 1 1 1 ]\n");
}
TEST_CASE("unari operators")
{
    stringstream s;
    std::vector<double> big_mat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -11, -13, -14, -12, 15, 16};
    Matrix big{big_mat, 4, 4};

    s.str("");
    s << (+big); // check all positive
    CHECK(s.str() == "[ 1 2 3 4 ]\n"
                     "[ 5 6 7 8 ]\n"
                     "[ 9 10 11 13 ]\n"
                     "[ 14 12 15 16 ]\n");
    s.str("");
    s << (-big); // check all negative
    CHECK(s.str() == "[ -1 -2 -3 -4 ]\n"
                     "[ -5 -6 -7 -8 ]\n"
                     "[ -9 -10 -11 -13 ]\n"
                     "[ -14 -12 -15 -16 ]\n");
    s.str("");
    s << (-(+big));
    CHECK(s.str() == "[ -1 -2 -3 -4 ]\n"
                     "[ -5 -6 -7 -8 ]\n"
                     "[ -9 -10 -11 -13 ]\n"
                     "[ -14 -12 -15 -16 ]\n");
    s.str("");
    s << (+(-big));
    CHECK(s.str() == "[ 1 2 3 4 ]\n"
                     "[ 5 6 7 8 ]\n"
                     "[ 9 10 11 13 ]\n"
                     "[ 14 12 15 16 ]\n");
    s.str("");
    s << (-(+(-(+(-(-(+big))))))); // check all negative after chaining operators
    CHECK(s.str() == "[ -1 -2 -3 -4 ]\n"
                     "[ -5 -6 -7 -8 ]\n"
                     "[ -9 -10 -11 -13 ]\n"
                     "[ -14 -12 -15 -16 ]\n");
    s.str("");
    s << (+(-(+(-(+(-(+(-big)))))))); // check all positive after chaining operators
    CHECK(s.str() == "[ 1 2 3 4 ]\n"
                     "[ 5 6 7 8 ]\n"
                     "[ 9 10 11 13 ]\n"
                     "[ 14 12 15 16 ]\n");
}
TEST_CASE("scalar multiplication")
{
    stringstream s;
    std::vector<double> _mat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -11, -13, -14, -12, 15, 16};
    Matrix mat{_mat, 4, 4};
    s.str("");
    s << (-1 * mat); // same as -mat
    CHECK(s.str() == "[ -1 -2 -3 -4 ]\n"
                     "[ -5 -6 -7 -8 ]\n"
                     "[ -9 -10 11 13 ]\n"
                     "[ 14 12 -15 -16 ]\n");
    s.str("");
    s << (1 * mat); // check that remain the same as before
    CHECK(s.str() == "[ 1 2 3 4 ]\n"
                     "[ 5 6 7 8 ]\n"
                     "[ 9 10 -11 -13 ]\n"
                     "[ -14 -12 15 16 ]\n");
    s.str("");
    s << (2 * mat);
    CHECK(s.str() == "[ 2 4 6 8 ]\n"
                     "[ 10 12 14 16 ]\n"
                     "[ 18 20 -22 -26 ]\n"
                     "[ -28 -24 30 32 ]\n");
    s.str("");
    s << (-2 * mat);
    CHECK(s.str() == "[ -2 -4 -6 -8 ]\n"
                     "[ -10 -12 -14 -16 ]\n"
                     "[ -18 -20 22 26 ]\n"
                     "[ 28 24 -30 -32 ]\n");
    s.str("");
    s << (0.5 * mat);
    CHECK(s.str() == "[ 0.5 1 1.5 2 ]\n"
                     "[ 2.5 3 3.5 4 ]\n"
                     "[ 4.5 5 -5.5 -6.5 ]\n"
                     "[ -7 -6 7.5 8 ]\n");
    s.str("");
    s << (-0.5 * (0.5 * mat)); // check that it actually like -0.25*mat
    CHECK(s.str() == "[ -0.25 -0.5 -0.75 -1 ]\n"
                     "[ -1.25 -1.5 -1.75 -2 ]\n"
                     "[ -2.25 -2.5 2.75 3.25 ]\n"
                     "[ 3.5 3 -3.75 -4 ]\n");
    s.str("");
    mat *= 0.5;
    s << (1 * mat);
    CHECK(s.str() == "[ 0.5 1 1.5 2 ]\n"
                     "[ 2.5 3 3.5 4 ]\n"
                     "[ 4.5 5 -5.5 -6.5 ]\n"
                     "[ -7 -6 7.5 8 ]\n");
}
TEST_CASE("comparing")
{
    std::vector<double> _mat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -11, -13, -14, -12, 15, 16};
    Matrix mat{_mat, 4, 4};
    Matrix mat_same{_mat, 4, 4};
    CHECK_FALSE(!(mat == mat_same));
    CHECK_FALSE(mat != mat_same);
    std::vector<double> big_mat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::vector<double> another_big_mat = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    Matrix big_m{big_mat, 4, 4};
    Matrix a_m{another_big_mat, 4, 4};
    CHECK_FALSE(!(big_m < a_m));  // should be bigger by 16
    CHECK_FALSE(!(big_m <= a_m)); // should be bigger by 16
    CHECK_FALSE(big_m > a_m);     // should be smaller by 16
    CHECK_FALSE(big_m >= a_m);    // should be smaller by 16
    std::vector<double> big_mat_1 = {1, 2, 3, 45, 78, 4, 4, 5, 6, 97, 66, -9, 16, 1, 3, 22, 44, 12, 33, 41, 0, -9, 14, 12, 10, 8, 23, -9, -2, 11};
    std::vector<double> another_mat = {21, 34, 11, 57, 42, 0, 55, 12, 6, 12, 56, 8, 23, 78, 9, 13, 41, 5};
    Matrix big{big_mat_1, 5, 6};
    Matrix same_row_size{another_mat, 6, 3};
    CHECK_FALSE(((-big) * same_row_size) == ((+big) * same_row_size));    // check that not the same
    CHECK_FALSE(!(((-big) * same_row_size) != ((+big) * same_row_size))); // check that not the same
}
TEST_CASE("invalid sizes")
{
    std::vector<double> _mat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -11, -13, -14, -12, 15, 16};
    Matrix mat{_mat, 4, 4};
    Matrix mat_smaller{_mat, 3, 4};
    CHECK_THROWS(mat * mat_smaller); // can't multiply matrix that the left col size is different from the right row size
    Matrix m{5, 5};
    Matrix b{5, 4};
    CHECK_THROWS(m + b);  // can't sum matrix with different size
    CHECK_THROWS(m - b);  // can't substruct matrix with different size
    CHECK_THROWS(b * m);  // can't multiply matrix that the left col size is different from the right row size
    CHECK_NOTHROW(m * b); // can't multiply matrix that the left col size is different from the right row size
    std::vector<double> big_mat_1 = {1, 2, 3, 45, 78, 4, 4, 5, 6, 97, 66, -9, 16, 1, 3, 22, 44, 12, 33, 41, 0, -9, 14, 12, 10, 8, 23, -9, -2, 11};
    std::vector<double> another_mat = {21, 34, 11, 57, 42, 0, 55, 12, 6, 12, 56, 8, 23, 78, 9, 13, 41, 5};
    Matrix big{big_mat_1, 5, 6};
    Matrix same_row_size{another_mat, 5, 3};
    CHECK_THROWS(big * same_row_size);       // can't multiply matrix that the left col size is different from the right row size
    CHECK_THROWS(same_row_size * big);       // can't multiply matrix that the left col size is different from the right row size
    CHECK_THROWS(Matrix(another_mat, 5, 5)); // can't create matrix with more cells than the vector size
    CHECK_THROWS(Matrix(big_mat_1, 6, 6));   // can't create matrix with more cells than the vector size
    CHECK_THROWS(Matrix(big_mat_1, -6, 6));  // can't create matrix with negative values
    CHECK_THROWS(Matrix(big_mat_1, 6, -6));  // can't create matrix with negative values
    CHECK_THROWS(Matrix(big_mat_1, -1, -3)); // can't create matrix with negative values
}