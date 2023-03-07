#include <iostream>
#include "mymatrix.h"

using namespace std;


bool string_initialize_test(){
    mymatrix<string> matrix;
    for(int r = 0; r < matrix.numrows(); r++){
        for (int c = 0; c < matrix.numcols(r); ++c) {
            if(!matrix(r,c).empty()) return false;
        }
    }
    return true;
}

bool size_test(){
    mymatrix<bool> matrix;
    if(matrix.size() == 16)
        return true;
    cout << "size_test() failed" << endl;
    return false;
}

bool access_operator_test(){
    mymatrix<char> matrix;
    matrix(0,0) = 'a';
    if(matrix(0,0) == 'a')
        return true;
    cout << "access_operator_test() failed" << endl;
    return false;
}

bool parameterized_constructor_size_test(){
    mymatrix<double> matrix(20,20);
    if(matrix.size() == 400)
        return true;
    cout << "parameterized_constructor_size_test() failed" << endl;
    return false;
}

bool parameterized_constructor_edge_test(){
    mymatrix<int> matrix(20,20);
    if(matrix(19,19) == 0)
        return true;
    cout << "parameterized_constructor_edge_test() failed" << endl;
    return false;
}

bool copy_constructor_value_test(){
    mymatrix<int> matrix(20,20);
    matrix(0,0) = 1;
    mymatrix<int> copyMatrix(matrix);
    if(copyMatrix(0,0) == 1)
        return true;
    cout << "copy_constructor_value_test() failed" << endl;
    return false;
}

bool copy_constructor_size_test(){
    mymatrix<int> matrix(20,20);
    mymatrix<int> copyMatrix(matrix);
    if(copyMatrix.size() == 400)
        return true;
    cout << "copy_constructor_size_test() failed" << endl;
    return false;
}

bool copy_constructor_jagged_test(){
    mymatrix<int> matrix(20,20);
    matrix.growcols(9, 30);
    mymatrix<int> copyMatrix(matrix);
    if(copyMatrix.numcols(9) == 30)
        return true;
    cout << "copy_constructor_jagged_test() failed" << endl;
    return false;
}

bool numrows_test(){
    mymatrix<int> matrix(20,30);
    if(matrix.numrows() == 20)
        return true;
    cout << "numrows_test() failed" << endl;
    return false;
}

bool numcols_test(){
    mymatrix<int> matrix(20,30);
    if(matrix.numcols(0) == 30)
        return true;
    cout << "numcols_test() failed" << endl;
    return false;
}

bool numcols_jagged_test(){
    mymatrix<int> matrix(20,30);
    matrix.growcols(10, 40);
    if(matrix.numcols(10) == 40 && matrix.numcols(0) == 30)
        return true;
    cout << "numcols_jagged_test() failed" << endl;
    return false;
}

bool growcols_test1(){
    mymatrix<int> matrix(20,20);
    matrix.growcols(0, 30);
    if(matrix.size() == 410)
        return true;
    cout << "growcols_test1() failed" << endl;
    return false;
}

bool growcols_test2(){
    mymatrix<double> matrix(20,20);
    matrix.growcols(10, 30);
    matrix(10, 29) = 1;
    if(matrix(10, 29) == 1 && matrix(10, 19) == 0)
        return true;
    cout << "growcols_test2() failed" << endl;
    return false;
}

bool out_of_bounds_exception(){
    try {
        mymatrix<int>  matrix;
        matrix(10,10) = 1;
        cout << "out_of_bounds_test() failed" << endl;
        return false;
    }
    catch (invalid_argument & x) {
        return true;
    }
}

bool grow_num_of_rows_exception(){
    try {
        mymatrix<int>  matrix;
        matrix.grow(-1,10);
        cout << "grow_num_of_rows_test() failed" << endl;
        return false;
    }
    catch (invalid_argument & x) {
        return true;
    }
}

bool grow_jagged_test(){
    mymatrix<int>  matrix;
    matrix.growcols(0, 10);
    matrix.grow(20, 20);
    if(matrix.size() == 400)
        return true;
    cout << "grow_jagged_test() failed" << endl;
    return false;
}

bool grow_rectangular_test(){
    mymatrix<int>  matrix;
    matrix.growcols(0, 10);
    matrix.grow(20, 20);
    return matrix.is_rectangular();
}

bool grow_value_test(){
    mymatrix<int>  matrix;
    matrix(0,0) = 1;
    matrix.grow(20, 20);
    matrix(19,19) = 1;
    if(matrix(0,0) == 1 && matrix(19,19) == 1)
        return true;
    cout << "grow_value_test() failed" << endl;
    return false;
}

bool at_exception(){
    try {
        mymatrix<int>  matrix;
        matrix.at(10,10);
        cout << "at_exception() failed" << endl;
        return false;
    }
    catch (invalid_argument & x) {
        return true;
    }
}

bool at_change_test(){
    mymatrix<string> matrix;
    matrix.at(1,3) = "Hello";
    if(matrix(1,3) == "Hello" && matrix.at(1,3) == "Hello")
        return true;
    cout << "at_change_test() failed" << endl;
    return false;
}

bool scalar_test(){
    mymatrix<int> matrix;
    matrix(0,0) = 1;
    matrix(3,3) = 1;
    matrix = matrix * 2;
    if(matrix(0,0) == 2 && matrix(3,3) == 2)
        return true;
    cout << "scalar_test() failed" << endl;
    return false;
}

bool scalar_jagged_test(){
    mymatrix<int> matrix;
    matrix.growcols(1, 10);
    matrix(1, 9) = 1;
    matrix(0,0) = 1;
    matrix(3,3) = 1;
    matrix = matrix * 2;
    if(matrix(0,0) == 2 && matrix(3,3) == 2 && matrix(1, 9) == 2)
        return true;
    cout << "scalar_jagged_test() failed" << endl;
    return false;
}

bool is_rectangular_test(){
    mymatrix<char> matrix;
    matrix.growcols(0, 20);
    if(!matrix.is_rectangular())
        return true;
    cout << "is_rectangular_test() failed" << endl;
    return false;
}

bool matrix_compatible_exception(){
    try {
        mymatrix<int>  m1(10,20);
        mymatrix<int>  m2(17,5);
        mymatrix<int>  result;
        result = m1 * m2;
        cout << "matrix_compatible_exception() failed" << endl;
        return false;
    }
    catch (runtime_error & x) {
        return true;
    }
}

bool multiplication_test(){
    mymatrix<int>  m1(4,10);
    mymatrix<int>  m2(10,7);
    mymatrix<int>  result = m1 * m2;
    if(result.size() == 28)
        return true;
    cout << "multiplication_test() failed" << endl;
    return false;
}

bool multiplication_test2(){
    mymatrix<int>  m1(4,10);
    mymatrix<int>  m2(10,7);
    m1(0,0) = 7;
    m1(3,9) = 7;
    m2(4,3) = 7;
    m2(9,6) = 7;
    mymatrix<int>  result = m1 * m2;
    if(result(3,6) == 49)
        return true;
    cout << "multiplication_test2() failed" << endl;
    return false;
}




int main() {

    int passed = 0;
    int failed = 0;

    string_initialize_test() ? passed++ : failed++;
    size_test() ? passed++ : failed++;
    access_operator_test() ? passed++ : failed++;
    parameterized_constructor_size_test() ? passed++ : failed++;
    parameterized_constructor_edge_test() ? passed++ : failed++;
    copy_constructor_value_test() ? passed++ : failed++;
    copy_constructor_size_test() ? passed++ : failed++;
    copy_constructor_jagged_test() ? passed++ : failed++;
    numrows_test() ? passed++ : failed++;
    numcols_test() ? passed++ : failed++;
    numcols_jagged_test() ? passed++ : failed++;
    growcols_test1() ? passed++ : failed++;
    growcols_test2() ? passed++ : failed++;
    out_of_bounds_exception() ? passed++ : failed++;
    grow_num_of_rows_exception() ? passed++ : failed++;
    grow_jagged_test() ? passed++ : failed++;
    grow_rectangular_test() ? passed++ : failed++;
    grow_value_test() ? passed++ : failed++;
    at_exception() ? passed++ : failed++;
    at_change_test() ? passed++ : failed++;
    scalar_test() ? passed++ : failed++;
    scalar_jagged_test() ? passed++ : failed++;
    is_rectangular_test() ? passed++ : failed++;
    matrix_compatible_exception() ? passed++ : failed++;
    multiplication_test() ? passed++ : failed++;
    multiplication_test2() ? passed++ : failed++;


    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

    return 0;
}
