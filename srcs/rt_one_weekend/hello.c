#include "minirt.h"

typedef struct s_icolor
{
    int     r;
    int     g;
    int     b;
    double  h_divider;
    double  w_divider;
}   t_icolor;

void    hello_world(t_data *rt)
{
    t_icolor t;

    t.h_divider = 1.0f / (IMG_H - 1);
    t.w_divider = 1.0f / (IMG_W - 1);
    for (int i = 0; i < IMG_H; i++) {
        for (int j = 0; j < IMG_W; j++) {
            t.r = 256.0f * j * t.w_divider;
            t.g = 256.0f * i * t.h_divider;
            t.b = 64;           
            fill_pixel(rt->img, i, j, int_to_color(t.r, t.g, t.b));
        }
    }
    display_default(rt);
}