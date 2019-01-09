#ifndef CG_RAYTRACER_VECTOR_H
#define CG_RAYTRACER_VECTOR_H

typedef struct SVector
{
    float x, y, z;
} Vector;

Vector vector_add(Vector v1, Vector v2);
Vector vector_sub(Vector v1, Vector v2);
Vector vector_mul(Vector v, float value);
Vector vector_div(Vector v, float value);
Vector vector_reflect(Vector vector, Vector normal);
float vector_dot(Vector v1, Vector v2);
float vector_length(Vector v);

#endif //CG_RAYTRACER_VECTOR_H
