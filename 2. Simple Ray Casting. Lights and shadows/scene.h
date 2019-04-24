#ifndef CG_RAYTRACER_1_SCENE_H
#define CG_RAYTRACER_1_SCENE_H

#include "types.h"

typedef struct SScene
{
    Camera Camera;

    Sphere* Spheres;
    int SpheresCount;

    Light* Lights;
    int LightsCount;
} Scene;

Scene* createScene();
void freeScene(Scene* scene);

#endif //CG_RAYTRACER_1_SCENE_H
