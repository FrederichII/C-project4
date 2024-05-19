#include <iostream>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <random>
#include <fstream>

#define TEMPLATE template <typename T>
using namespace std;

class MyChar
{
    char val;

public:
    MyChar(char val) : val(val) {}
    char get()
    {
        return this->val;
    }
    char operator+(MyChar &other)
    {
        int result;
        result = static_cast<int>(val) + static_cast<int>(other.val);
        if (result > 127)
        {
            result = result - 128;
        }
        return static_cast<char>(result);
    }
};

TEMPLATE
class Matrix
{

    static_assert(std::is_same<T, int>::value || std::is_same<T, char>::value ||
                      std::is_same<T, float>::value || std::is_same<T, double>::value,
                  "T must be int, char, float or double");

    size_t rows;
    size_t cols;
    shared_ptr<T> data;

public:
    

    bool mat_multiply(Matrix *pa, Matrix *pb, Matrix *pout)
    {
        if (*pa.cols != *pb.cols || *pa.rows != *pb.rows)
        {
            printf("the two matrices have different sizes, cannot be multiplied, (rows,cols) of a: (%zu,%zu), (rows,cols) of b: (%zu,%zu),",
                   *pa.rows, *pa.cols, *pb.rows, *pb.cols);
            return false;
        }

        size_t m = pa->rows;
        size_t n = pa->cols;
        size_t p = pb->cols;
        
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < p; j++)
            {

                shared_ptr<T> prowA = make_shared(*(pa->data)[i * m]);
                shared_ptr<T> prowB = make_shared(*(pb->data)[j]);
                pout->data[i * m + j] = 0; // 初始化
                for (size_t k = 0; k < n; k++)
                {
                    pout->data[i * m + j] += prowA[k] * prowB[k];
                }
            }
        }
        return true;
    }

    bool mat_add(Matrix *pa, Matrix *pb, Matrix *pout)
    {
        if (pa->cols != pb->rows || pa->rows != pb->rows)
        {
            printf("the two matrices have different sizes, cannot be added, (rows,cols) of a: (%zu,%zu), (rows,cols) of b: (%zu,%zu),",
                   pa->rows, pa->cols, pb->rows, pb->rows);
            return false;
        }
        for (size_t i = 0; i < pa->cols * pb->rows; i++)
        {
            if (is_same<T, char>::value)
            {
                MyChar* char_a = new MyChar(pa->data.get()[i]);
                MyChar* char_b = new MyChar(pb->data.get()[i]);
                pout->data.get()[i] = char_a->get() + char_b->get(); // Operator already overloaded for char add in matrix.hpp
            }
            pout->data.get()[i] = pa->data.get()[i] + pb->data.get()[i];
        }
        return true;
    }

    bool AssignRandomValue(float begin, float end, Matrix *pmat)
    {
        static default_random_engine generator(time(0));

        if (is_integral<T>::value)
        {
            uniform_int_distribution<T> distribution(begin, end);
            for (size_t i = 0; i < pmat->rows * (pmat->cols); i++)
            {
                pmat->data.get()[i] = T(distribution(generator));
            }
        }
        else if (is_same<T, float>::value || is_same<T, double>::value)
        {
            uniform_real_distribution<T> distribution(begin, end);
            for (size_t i = 0; i < pmat->rows * (pmat->cols); i++)
            {
                pmat->data.get()[i] = T(distribution(generator));
            }
        }
        else if (is_same<T, char>::value)
        {
            uniform_int_distribution<T> distribution(begin, end);
            for (size_t i = 0; i < pmat->rows * (pmat->cols); i++)
            {
                pmat->data.get()[i] = T(distribution(generator) % 128);
            }
        }
        return true;
    }

    bool AssignSameValue(T value, Matrix *pmat)
    {
        for (size_t i = 0; i < pmat->rows * pmat->cols; i++)
        {
            pmat->data.get()[i] = value;
        }
        return true;
    }

    bool printMatrix(Matrix *pmat)
    {
        if (is_same<T, int>::value)
        {
            for (size_t i = 0; i < pmat->rows; i++)
            {
                for (size_t j = 0; j < pmat->cols; j++)
                {
                    printf("%d\t", pmat->data.get()[i * pmat->rows + j]);
                }
                printf("\n");
            }
            return true;
        }
        else if (is_same<T, double>::value || is_same<T, float>::value)
        {
            for (size_t i = 0; i < pmat->rows; i++)
            {
                for (size_t j = 0; j < pmat->cols; j++)
                {
                    printf("%f\t", pmat->data.get()[i * pmat->rows + j]);
                }
                printf("\n");
            }
            return true;
        }
        else if (is_same<T, char>::value)
        {
            for (size_t i = 0; i < pmat->rows; i++)
            {
                for (size_t j = 0; j < pmat->cols; j++)
                {
                    printf("%c\t", pmat->data.get()[i * pmat->rows + j]);
                }
                printf("\n");
            }
            return true;
        }
        else
        {
            printf("Error: type of T must be one of the four: int, float, double, char\n");
            return false;
        }
    }

    bool writeMatirxToCSV(Matrix *pmat, string filename)
    {
        std::ofstream outFile(filename);

        if (!outFile)
        {
            cerr << "Error: Could not open the file!" << endl;
            return false;
        }

        for (size_t i = 0; i < pmat->rows; i++)
        {
            for (size_t j = 0; j < pmat->cols; j++)
            {
                outFile << pmat(i, j);
            }
        }

        outFile.close();

        if (outFile.fail())
        {
            std::cerr << "Error: Could not close the file!" << std::endl;
        }
    }

    Matrix() : rows(0),
               cols(0)
    {
        data = make_shared<T>(0);
    }

    Matrix(size_t rows, size_t cols) : rows(rows),
                                       cols(cols)
    {
        data = make_shared<T>(0);
    }
    // copy constructor
    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols), data(new T[other.rows * other.cols]())
    {
        copy(other.data.get(), other.data.get() + (other.rows * other.cols), data.get());
    }

    // operator overloading for element access
    const T &operator()(size_t i, size_t j) const
    {
        if (i >= rows || j >= cols)
        {
            throw out_of_range("Index out of range");
        }
        return data[i * cols + j];
    }

    // operator overloading for matrix addition

    Matrix operator*(Matrix &other)
    {
        if (cols != other.rows)
        {
            printf("the two matrices cannot be multiplied due to dimension, (rows,cols) of a: (%zu,%zu), (rows,cols) of b: (%zu,%zu),",
                   rows, cols, other.rows, other.cols);
            exit(EXIT_FAILURE);
        }
        Matrix out = Matrix(rows, other.cols);
        bool result = mat_multiply(this, &other, &out);
        if (result)
        {
            return out;
        }
        else
        {
            cout << "exiting..." << endl;
        }
    }

    // operator overloading for matrix multiplication
    Matrix operator+(Matrix &other)
    {
        Matrix out = Matrix(rows, other.cols);
        bool result = mat_add(this, &other, &out);
        if (result)
        {
            return out;
        }
        else
        {
            cout << "exiting..." << endl;
            exit(EXIT_FAILURE);
        }
    }
};
