#ifndef CG_RAYTRACER_COLOR_H
#define CG_RAYTRACER_COLOR_H

typedef struct SColor
{
    unsigned char r, g, b;
} Color;

Color color_mul(Color color, float value);
Color color_add(Color c1, Color c2);
Color color_blend(Color c1, Color c2, float f);

#endif //CG_RAYTRACER_COLOR_H
