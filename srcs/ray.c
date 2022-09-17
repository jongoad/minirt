#include "minirt.h"

/* Generate a primary ray for a specific pixel */
t_ray	*generate_primary_ray(t_data *data, int x, int y)
{
	t_ray *ray;

	ray = ft_xalloc(sizeof(t_ray));
	ray->second = init_pixel_point(data, x, y);
	ray->vec3 = get_vector(ray->origin, ray->second);
	return (ray);
}

/* Generate a vector based on an origin point and secondary point */
t_vector	*get_vector(t_point *origin, t_point *second)
{
	t_vector *vector;

	vector = ft_xalloc(sizeof(t_vector));
	vector->x = second->x - origin->x;
	vector->y = second->y - origin->y;
	vector->z = second->z - origin->z;
	return (vector);
}

/* Return a secondary point based on current camera location */
t_point		*init_pixel_point(t_data *data, int x, int y)
{
	t_point *point;
	t_data	*data;
	float	width;
	float	height;

	point = ft_xalloc(sizeof(t_point));
	data = get_data();
	
	/* Calculate center of pixel point in image plane */
	width = data->cam.view_w / data->cam.img_w;							/* Take the width of image plane and divide by image_width (number of pixels) */
	point->x = (width * (x + 1)) - ((x + 1) * 0.5);						/* Then take multiply this value by the x value passed to function, and subtract half of width of one pixel */
	height = data->cam.view_h / data->cam.img_h;
	point->y = (height * (y + 1)) - ((y + 1) * 0.5);
	point->z = 0;
	point->w = 1;

	/* Now the point needs to be transformed from local space into world space */
	matrix_mult_point(point, data->cam.cam_to_world);					

	return (point);
}
/* Our array will be 0-indexed, but the x and y values for this function need to be 1-indexed */