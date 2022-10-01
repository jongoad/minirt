#include "minirt.h"

int     int_to_color(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

t_vec3  color_to_vec3(int c)
{
    return (vec3(
        ((c >> 16) & 0xFF),
        ((c >> 8) & 0xFF),
        (c & 0xFF)));
}

int     vec3_to_color(t_vec3 c)
{
    return ((int)c.x << 16) | ((int)c.y << 8) | (int)c.z;
}

int     vec3_to_color_copy(t_vec3 c)
{
    return ((int)c.x << 16) | ((int)c.y << 8) | (int)c.z;
}
