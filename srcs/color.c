#include "minirt.h"

int    to_color(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}
