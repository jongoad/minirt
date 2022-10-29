#include "minirt.h"

t_color     int_to_color(int c)
{
    t_color clr;

    clr.r = (c >> 16) & 0xFF;
    clr.g = (c >> 8) & 0xFF;
    clr.b = c & 0xFF;
    return (clr);
}

int     color_to_int(t_color c)
{
    return ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b;
}

t_vec3     color_to_vec3(t_color c)
{
    return (vec3(c.r, c.g, c.b));
}

t_color lerp_color(t_color a, t_color b, float factor)
{
    t_color diff;
    
    if (factor <= 0.0F)
    {
        return (a);
    }
    else if (factor > 1.0F)
    {
        return (b);
    }
    diff.r = a.r + (b.r - a.r) * factor;
    diff.g = a.g + (b.g - a.g) * factor;
    diff.b = a.b + (b.b - a.b) * factor;
    return (diff);
}

t_color color_x_vec3(t_color col, t_vec3 factor)
{
    t_color diff;
    
    if (factor.x > 1.0F || factor.x < 0.0
        || factor.y > 1.0F || factor.y < 0.0
        || factor.z > 1.0F || factor.z < 0.0)
    {
        ft_putstr_fd("Error, wrong color factor\n", 2);
        return (col);
    }
    diff.r = col.r * factor.x;
    diff.g = col.g * factor.y;
    diff.b = col.b * factor.z;
    return (diff);
}
