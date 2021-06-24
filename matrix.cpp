#include "matrix.h"

Matrix::Matrix(std::initializer_list<row> matrix) : std::vector<row>(matrix)
{
    rowCount = matrix.size();
    columnCount = matrix.begin()->size();
}

Matrix::Matrix(int rows, int columns) : std::vector<row>(rows, row(columns))
{
    rowCount = rows;
    columnCount = columns;
}

const Matrix Matrix::operator*(const Matrix &obj) const
{
    Matrix res(rowCount, obj.columnCount);

    for (int j = 0; j < rowCount; j++)
    {
        for (int i = 0; i < res.columnCount; i++)
        {
            for (int k = 0; k < columnCount; k++)
            {
                res[j][i] += (*this)[j][k] * obj[k][i];
            }
        }
    }

    return res;
}

