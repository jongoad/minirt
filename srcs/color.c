#include "minirt.h"

int     int_to_color(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

void    color(t_color *c)
{
    c->color = (c->r << 16) | (c->g << 8) | c->b;
}

int     vec3_to_color(t_vec3 *c)
{
    return ((int)c->x << 16) | ((int)c->y << 8) | (int)c->z;
}

int     vec3_to_color_copy(t_vec3 c)
{
    return ((int)c.x << 16) | ((int)c.y << 8) | (int)c.z;
}
