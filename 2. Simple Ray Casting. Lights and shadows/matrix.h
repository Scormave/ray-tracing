#ifndef CG_RAYTRACER_MATRIX_H
#define CG_RAYTRACER_MATRIX_H

#include "vector.h"

typedef struct SMatrix
{
    float data[3][3];
} Matrix;

Vector matrix_vector_mul(Matrix m, Vector v);
Matrix matrix_matrix_mul(Matrix m1, Matrix m2);

#endif //CG_RAYTRACER_MATRIX_H
