#include "matrix.h"

Vector matrix_vector_mul(Matrix m, Vector v)
{
    Vector result;
    result.x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z;
    result.y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z;
    result.z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z;
    return result;
}

Matrix matrix_matrix_mul(Matrix m1, Matrix m2)
{
    Matrix result;
    float sum = 0.0;
    for (int c = 0; c < 3; c++)
    {
        for (int d = 0; d < 3; d++)
        {
            for (int k = 0; k < 3; k++)
            {
                sum = sum + m1.data[c][k]*m2.data[k][d];
            }

            result.data[c][d] = sum;
            sum = 0;
        }
    }
    return result;
}