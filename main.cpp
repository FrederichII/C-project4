#include <iostream>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <type_traits>
#include "matrix.hpp"

using namespace std;
int main()
{
    Matrix<double> mat_double_1 = Matrix<double>(5, 5);
    Matrix<double> mat_double_2 = Matrix<double>(5, 5);
    mat_double_1.AssignRandomValue(1, 10, &mat_double_1);
    mat_double_2.AssignRandomValue(1, 10, &mat_double_2);
    Matrix<double> mat_double_ROI = mat_double_ROI.ROI(0,1,0,1,&mat_double_1);
    mat_double_1.printMatrix(&mat_double_1);
    cout << endl;
    mat_double_2.printMatrix(&mat_double_2);
    cout << endl;
    mat_double_ROI.printMatrix(&mat_double_ROI);
    cout<<endl;
    
}