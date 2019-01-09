#include "ray.h"

Ray createRay(Vector origin, Vector direction)
{
    return (Ray) { origin, direction, vector_dot(direction, direction) };
}