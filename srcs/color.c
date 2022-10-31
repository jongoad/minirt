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

void    clamp_color(t_color *c)
{
    if (c->r < 0)
        c->r = 0;
    else if (c->r > 255)
        c->r = 255;
    if (c->g < 0)
        c->g = 0;
    else if (c->g > 255)
        c->g = 255;
    if (c->b < 0)
        c->b = 0;
    else if (c->b > 255)
        c->b = 255;
}

t_color mult_color(t_color rgb, float factor)
{
    t_color diff;
    

    diff.r = rgb.r * factor > 255 ? 255 : rgb.r * factor;
    diff.g = rgb.g * factor > 255 ? 255 : rgb.g * factor;
    diff.b = rgb.b * factor > 255 ? 255 : rgb.b * factor;
    clamp_color(&diff);
    return (diff);
}

t_color add_color(t_color a, t_color b)
{
    t_color diff;
    
    diff.r = a.r + b.r > 255 ? 255 : a.r + b.r;
    diff.g = a.g + b.g > 255 ? 255 : a.g + b.g;
    diff.b = a.b + b.b > 255 ? 255 : a.b + b.b;
    clamp_color(&diff);
    return (diff);
}

t_color color_x_vec3(t_color col, t_vec3 factor)
{
    t_color diff;
    
    if (factor.x > 1.0F || factor.x < 0.0
        || factor.y > 1.0F || factor.y < 0.0
        || factor.z > 1.0F || factor.z < 0.0)
    {
        // ft_putstr_fd("Error, wrong color factor \n", 2);
        // print_vec3(factor);
        // printf("\n");
        // return (col);
    }
    diff.r = col.r * factor.x > 255 ? 255 : col.r * factor.x;
    diff.g = col.g * factor.y > 255 ? 255 : col.g * factor.y;
    diff.b = col.b * factor.z > 255 ? 255 : col.b * factor.z;
    return (diff);
}
