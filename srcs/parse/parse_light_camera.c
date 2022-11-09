#include "minirt.h"

/* Parse ambient light (A) */
int	parse_ambient(char **obj)
{
	t_i	i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 3)
		return (0);
	if (!check_float(obj[1], 0.0f, 1.0f))	/* Ensure light intensity is within defined range */
		return (0);
	if (!check_rgb(obj[2]))					/* Ensure RGB values are within range and valid */
		return (0);
	return (1);
}

/* Parse camera (C) */
int	parse_camera(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 4)
		return (0);
	if (!check_coords(obj[1]))				/* Check position data */
		return (0);
	if (!check_orientation(obj[2]))			/* Check orientation vector */
		return (0);
	if (!check_int(obj[3], 0, 180))			/* Ensure FOV value is within range */
		return (0);
	return (1);
}

/* Parse point light (L) */
int	parse_light(char **obj)
{
	t_i	i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x < 3)
		return (0);
	if (!check_coords(obj[1]))				/* Check position data */
		return (0);
	if (!check_float(obj[2], 0, 1))			/* Ensure light intensity is within defined range */
		return (0);
	if (BONUS == 1)
		if (i.x == 4)
			if (!check_rgb(obj[3]))			/* Ensure RGB values are within range and valid */
				return (0);
	return (1);
}
