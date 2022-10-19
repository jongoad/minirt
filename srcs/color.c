#include "minirt.h"

t_color     int_to_color(int c)
{
    t_color clr;

    clr.r = (c >> 16) & 0xFF;
    clr.g = (c >> 8) & 0xFF;
    clr.b = c & 0xFF;
    return (clr);
}

t_vec3  int_to_vec3(int c)
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

int     color_to_int(t_color c)
{
    return ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b;
}

t_vec3	color_to_vec3(t_color c)
{
    return (vec3(c.r, c.g, c.b));
}


int     vec3_to_color_copy(t_vec3 c)
{
    return ((int)c.x << 16) | ((int)c.y << 8) | (int)c.z;
}
 