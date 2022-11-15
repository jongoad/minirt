#include "minirt.h"

/* Convert integer color value to RGB component color*/
t_color	 int_to_color(int c)
{
	t_color clr;

	clr.r = (c >> 16) & 0xFF;
	clr.g = (c >> 8) & 0xFF;
	clr.b = c & 0xFF;
	return (clr);
}

/* Convert RGB component color to a single integer color value */
int	 color_to_int(t_color c)
{
	return ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b;
}

t_vec3	 color_to_vec3(t_color c)
{
	return (vec3(c.r, c.g, c.b));
}

/* Find linear interpolation between two colors using a weight factor variable */
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
