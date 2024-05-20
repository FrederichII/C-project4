#include <iostream>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <type_traits>
#include "matrix.hpp"

using namespace std;
int main()
{
    Matrix<int> mat1 =Matrix<int>(4,3);
    Matrix<int> mat2 =Matrix<int>(3,5);
    Matrix<int> mat3 =Matrix<int>(4,5);
    mat1.AssignRandomValue(1,10,&mat1);
    mat2.AssignRandomValue(1,10,&mat2);
    mat3 = mat1 * mat2;
    mat1.printMatrix(&mat1);
    printf("\n");
    mat2.printMatrix(&mat2);
    printf("\n");
    if(mat3.mat_multiply(&mat1,&mat2,&mat3)) printf("true\n");
    else printf("false\n");
    mat3.printMatrix(&mat3);
    mat3.writeMatrixToCSV(&mat3,"result.csv");
    return 0;
}