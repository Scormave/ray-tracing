#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include "png_render.h"
#include "ray.h"
#include "scene.h"
#include "types.h"

const int CanvasWidth = 512;
const int CanvasHeight = 512;
const float ViewportSize = 1.0;
const float ProjectionPlaneZ = 1.0;
Scene* RayTracingScene;

Color traceRay(Ray ray, float t_min, float t_max);
int intersectRaySphere(Ray ray, Sphere sphere, float* intersects);
Vector canvasToViewport(int x, int y);
Intersection closestIntersection(Ray ray, float t_min, float t_max);

int main()
{
    printf("Preparing for rendering...\n");
    unsigned char* buffer = malloc(CanvasWidth * 3);
    RayTracingScene = createScene();
    PNG* png = createPng("result.png", CanvasWidth, CanvasHeight, "Result");

    printf("Started rendering...\n");
    clock_t start = clock();

    for (int y = - CanvasHeight / 2; y < CanvasHeight / 2; y++)
    {
        for (int x = - CanvasWidth / 2; x < CanvasWidth / 2; x++)
        {
            Vector dir = matrix_vector_mul(RayTracingScene->Camera.rotation, canvasToViewport(x, y));
            Ray ray = createRay(RayTracingScene->Camera.position, dir);
            Color color = traceRay(ray, 1, INFINITY);

            int offset = (x + CanvasWidth / 2)*3;
            buffer[offset] = color.r;
            buffer[offset + 1] = color.g;
            buffer[offset + 2] = color.b;
        }

        writeRow(png, buffer);
    }

    clock_t end = clock();
    float seconds = (float)(end - start)*1000 / CLOCKS_PER_SEC;
    printf("Done! Elapsed time: %.00fms\n", seconds);
    
    free(buffer);
    freeScene(RayTracingScene);
    freePng(png);

    return 0;
}

Vector canvasToViewport(int x, int y)
{
    Vector result;
    result.x = (float)x * ViewportSize / CanvasWidth;
    result.y = (float)y * ViewportSize / CanvasHeight;
    result.z = ProjectionPlaneZ;
    return result;
}

Color traceRay(Ray ray, float t_min, float t_max)
{
    Intersection intersection = closestIntersection(ray, t_min, t_max);

    if (intersection.closest_sphere == NULL)
    {
        return RayTracingScene->Camera.backgroundColor;
    }

    return intersection.closest_sphere->color;
}

int intersectRaySphere(Ray ray, Sphere sphere, float* intersects)
{
    Vector oc = vector_sub(ray.origin, sphere.position);

    float k1 = ray.K;
    float k2 = 2 * vector_dot(oc, ray.direction);
    float k3 = vector_dot(oc, oc) - sphere.radius * sphere.radius;

    float discriminant = k2*k2 - 4*k1*k3;
    if (discriminant < 0)
    {
        intersects[0] = INFINITY;
        intersects[1] = INFINITY;
    }

    float t1 = (-k2 + sqrtf(discriminant)) / (2*k1);
    float t2 = (-k2 - sqrtf(discriminant)) / (2*k1);
    intersects[0] = t1;
    intersects[1] = t2;

    return 2;
}

Intersection closestIntersection(Ray ray, float t_min, float t_max)
{
    Intersection intersection = { NULL, INFINITY };
    for (int i = 0; i < RayTracingScene->SpheresCount; i++)
    {
        float intersects[2];
        int count = intersectRaySphere(ray, RayTracingScene->Spheres[i], intersects);
        for (int j = 0; j < count; j++)
        {
            if (intersects[j] > t_min && intersects[j] < t_max && intersects[j] < intersection.closest_t)
            {
                intersection.closest_t = intersects[j];
                intersection.closest_sphere = &RayTracingScene->Spheres[i];
            }
        }
    }
    return intersection;
}