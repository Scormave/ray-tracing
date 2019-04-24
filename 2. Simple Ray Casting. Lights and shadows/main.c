#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include "png_render.h"
#include "ray.h"
#include "scene.h"
#include "types.h"

const int CanvasWidth = 2048;
const int CanvasHeight = 2048;
const float ViewportSize = 1.0;
const float ProjectionPlaneZ = 1.0;
Scene* RayTracingScene;

Color traceRay(Ray ray, float t_min, float t_max);
int intersectRaySphere(Ray ray, Sphere sphere, float* intersects);
Vector canvasToViewport(int x, int y);
Intersection closestIntersection(Ray ray, float t_min, float t_max);
float computeLighting(Vector P, Vector N, Vector V, float s);

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

    Vector P = vector_add(ray.origin, vector_mul(ray.direction, intersection.closest_t));
    Vector N = vector_sub(P, intersection.closest_sphere->position);
    N = vector_div(N, vector_length(N));
    Vector minusDir = { -ray.direction.x, -ray.direction.y, -ray.direction.z };
    Color color = color_mul(intersection.closest_sphere->color, computeLighting(P, N, minusDir, intersection.closest_sphere->Specular));

    return color;
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

float computeLighting(Vector P, Vector N, Vector V, float s)
{
    float result = 0.0;
    Vector L;
    float t_max;

    for (int i = 0; i < RayTracingScene->LightsCount; i++)
    {
        Light light = RayTracingScene->Lights[i];
        if (light.type == Ambient)
        {
            result += light.intensity;
        }
        else
        {
            if (light.type == Point)
            {
                L = vector_sub(light.position, P);
                t_max = 1;
            }
            else
            {
                L = light.direction;
                t_max = INFINITY;
            }

            // Shadow
            Intersection shadow_intersection = closestIntersection(createRay(P, L), 0.001, t_max);
            if (shadow_intersection.closest_sphere != NULL)
                continue;

            // Diffuse
            float n_dot_l = vector_dot(N, L);
            if (n_dot_l > 0)
            {
                result += light.intensity * n_dot_l / (vector_length(N) * vector_length(L));
            }

            // Specular
            if (s > 0)
            {
                Vector R = vector_reflect(L, N);
                float r_dot_v = vector_dot(R, V);
                if (r_dot_v > 0)
                {
                    result += light.intensity * powf(r_dot_v / (vector_length(R) * vector_length(V)), s);
                }
            }
        }
    }

    return result;
}