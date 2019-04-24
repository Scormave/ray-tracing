#include <math.h>
#include "vector.h"

Vector vector_add(Vector v1, Vector v2)
{
    Vector result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

Vector vector_sub(Vector v1, Vector v2)
{
    Vector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

Vector vector_mul(Vector v, float value)
{
    Vector result;
    result.x = v.x * value;
    result.y = v.y * value;
    result.z = v.z * value;
    return result;
}

Vector vector_div(Vector v, float value)
{
    Vector result;
    result.x = v.x / value;
    result.y = v.y / value;
    result.z = v.z / value;
    return result;
}

Vector vector_reflect(Vector vector, Vector normal)
{
    return vector_sub(vector_mul(normal, 2 * vector_dot(normal, vector)), vector);
}

float vector_dot(Vector v1, Vector v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

float vector_length(Vector v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

