#ifndef CG_RAYTRACER_RAY_H
#define CG_RAYTRACER_RAY_H

#include "vector.h"

typedef struct SRay
{
    Vector origin;
    Vector direction;
    float K;
} Ray;

Ray createRay(Vector origin, Vector direction);

#endif //CG_RAYTRACER_RAY_H
