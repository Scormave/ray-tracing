#ifndef CG_RAYTRACER_TYPES_H
#define CG_RAYTRACER_TYPES_H

#include "vector.h"
#include "matrix.h"
#include "color.h"

typedef struct SCamera
{
    Vector position;
    Matrix rotation;
    Color backgroundColor;
} Camera;

enum LightType
{
    Ambient,
    Point,
    Directional
};

typedef struct SLight
{
    enum LightType type;
    float intensity;
    Vector position;
    Vector direction;
} Light;

typedef struct SSphere
{
    Vector position;
    float radius;
    Color color;
    float Specular;
} Sphere;

typedef struct SIntersection
{
    Sphere* closest_sphere;
    float closest_t;
} Intersection;

#endif //CG_RAYTRACER_TYPES_H
