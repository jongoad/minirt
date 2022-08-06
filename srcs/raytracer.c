#include "minirt.h"

void	raytracer(t_data *data)
{
	t_ray *ray;
	t_i i;

	float	dist;

	i.y = 0;
	i.x = 0;
	i.z = 0;
	while (i.y < IMG_H)
	{
		i.x = 0;
		while (i.x < IMG_W) // First 2 loops are to go through each pixel
		{
			ray = generate_primary_ray(data, i.x, i.y);		/* Generate the primary ray for this pixel */
			i.z = 0;
			while (i.z < data->nb_objs) //This loop is to go through each object in the scene
			{
				if (intersect(ray, data->objects[i.z]))
					//Check if dist is shorted than prev, if it is update object

				i.z++;
			}
			if (intersect found)
				/* Calculate shadow ray and set pixel based on result */
			else
				/* Set current pixel in image to ambient colout and brightness*/
			free_ray(ray);
			i.x++;
		}
		i.y++;
	}
}

int	intersect(t_ray *ray, t_object *object)
{
	//Calculate if the ray intersects with a given object
}

/* Basic raytracing steps:

1. Cast a ray for each pixel in the image
2. Test for ray-geometry intersection
3. Shading


Things to implement:
	- Acceleration structures
		e.g. a way to prevent intersections from needing to be calculated for each object.
			A simple way to do this would be to calculate the closest objects to the camera, and test those first
			then going in order of closest to furthest

			We could also generate an simple object intersection mask. If we rasterize all objects into a flat black and white image,
			we can then use this to test quickly if a ray will intersect anything.


- Change floats to doubles?
	- all math.h functions use doubles, this could improve integration
*/




