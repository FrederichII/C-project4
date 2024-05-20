#include <iostream>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <type_traits>
#include "matrix.hpp"

using namespace std;
int main()
{
    Matrix<double> mat1 =Matrix<double>(4,4);
    Matrix<double> mat2 =Matrix<double>(4,5);
    Matrix<double> mat3 =Matrix<double>(4,5);
    mat1.AssignRandomValue(33,126,&mat1);
    mat2.AssignRandomValue(33,126,&mat2);
    mat3 = (mat1 * mat2);
    mat1.printMatrix(&mat1);
    printf("\n");
    mat2.printMatrix(&mat2);
    printf("\n");
    if(mat3.mat_multiply(&mat1,&mat2,&mat3)) printf("true\n");
    else printf("false\n");
    mat3.printMatrix(&mat3);
    mat3.writeMatrixToCSV(&mat3,"result.csv");
    printf("%c\n",mat3(1,1));
    return 0;
}