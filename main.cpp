#include <iostream>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <type_traits>
#include "matrix.hpp"

using namespace std;
int main()
{
    Matrix<int> mat1 =Matrix<int>(3,3);
    Matrix<int> mat2 =Matrix<int>(3,3);
    mat1.AssignSameValue(1,&mat1);
    mat2.AssignSameValue(3,&mat2);
    mat1.printMatrix(&mat1);
    mat2.printMatrix(&mat2);
 
    return 0;
}