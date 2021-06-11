#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>

typedef std::vector<double> row;


class Matrix : public std::vector<row>
{
public:
    Matrix(std::initializer_list<row> matrix);

    Matrix(int rows, int columns);

    Matrix operator * (const Matrix &matrix);

private:
    int rowCount;
    int columnCount;
};

#endif // MATRIX_H
