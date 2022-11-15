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

/* Multiply color by a scale factor */
t_color mult_color(t_color rgb, float factor)
{
	int diff;

	diff = rgb.r * factor;
	rgb.r = diff;
	if (diff > 255)
		rgb.r = 255;
	else if (diff < 0)
		rgb.r = 0;
	
	diff = rgb.g * factor;
	rgb.g = diff;
	if (diff > 255)
		rgb.g = 255;
	else if (diff < 0)
		rgb.g = 0;	
	
	diff = rgb.b * factor;
	rgb.b = diff;
	if (diff > 255)
		rgb.b = 255;
	else if (diff < 0)
		rgb.b = 0;
	
	return (rgb);
}

/* Add two color values together*/
t_color add_color(t_color a, t_color b)
{
	int diff;
	
	diff = a.r + b.r;
	a.r = diff;
	if (diff > 255)
		a.r = 255;
	else if (diff < 0)
		a.r = 0;
		
	diff = a.g + b.g;
	a.g = diff;
	if (diff > 255)
		a.g = 255;
	else if (diff < 0)
		a.g = 0;	

	diff = a.b + b.b;
	a.b = diff;
	if (diff > 255)
		a.b = 255;
	else if (diff < 0)
		a.b = 0;

	return (a);
}

t_color color_x_vec3(t_color col, t_vec3 factor)
{
	int diff;
	
	diff = col.r * factor.x;
	col.r = diff;
	if (diff > 255)
		col.r = 255;
	else if (diff < 0)
		col.r = 0;
	
	diff = col.g * factor.y;
	col.g = diff;
	if (diff > 255)
		col.g = 255;
	else if (diff < 0)
		col.g = 0;	
	
	diff = col.b * factor.z;
	col.b = diff;
	if (diff > 255)
		col.b = 255;
	else if (diff < 0)
		col.b = 0;
	
	return (col);
}
