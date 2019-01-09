#include <malloc.h>
#include "scene.h"

Scene* createScene()
{
    Scene* scene = malloc(sizeof(Scene));

    // Init camera
    scene->Camera.position = (Vector){ 0.0f, 0.0f, -5.0f };
    scene->Camera.rotation = (Matrix){ 1.0f,  0.0000000f, 0.0f,
                                       0.0f, 1.0f, 0.0f,
                                       0.0f,  0.0000000f,  1.0f};
    scene->Camera.backgroundColor = (Color){ 255, 255, 255 };

    // Init spheres
    scene->SpheresCount = 4;
    scene->Spheres = malloc(sizeof(Sphere) * scene->SpheresCount);
    scene->Spheres[0] = (Sphere)
    {
        (Vector){ 1.0f, 1.0f, 4.0f },
        0.5f,
        (Color){ 255, 0, 255 }
    };
    scene->Spheres[1] = (Sphere)
    {
        (Vector){ -1.0f, -1.0f, 5.0f },
        1.0f,
        (Color){ 0, 255, 255 }
    };
    scene->Spheres[2] = (Sphere)
    {
        (Vector){ 0.0f, -5001.0f, 0.0f },
        5000.0f,
        (Color){ 255, 255, 0 }
    };
    scene->Spheres[3] = (Sphere)
    {
        (Vector){ 0.5f, 0.0f, 3.0f },
        0.5f,
        (Color){ 127, 127, 255 }
    };

    return scene;
}

void freeScene(Scene* scene)
{
    free(scene->Spheres);
    free(scene);
}