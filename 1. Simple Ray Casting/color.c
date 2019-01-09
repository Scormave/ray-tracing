#include "color.h"

Color color_mul(Color color, float value)
{
    Color result;
    result.r = (unsigned char)((float) color.r * value);
    result.g = (unsigned char)((float) color.g * value);
    result.b = (unsigned char)((float) color.b * value);
    return result;
}

Color color_add(Color c1, Color c2)
{
    Color result;
    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;
    return result;
}

Color color_blend(Color c1, Color c2, float f)
{
    Color col1 = color_mul(c1, 1 - f);
    Color col2 = color_mul(c2, f);
    return color_add(col1, col2);
}