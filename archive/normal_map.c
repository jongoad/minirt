#include "minirt.h"






t_vec3 normal_image_to_vec3(t_uv pos, t_ppm image)
{
	t_vec3 normal;

	normal.x = (((float)image.pixels[pos.v][pos.u].r / 255.0f) * 2.0f) - 1.0f;
	normal.y = (((float)image.pixels[pos.v][pos.u].g / 255.0f) * 2.0f) - 1.0f;
	normal.z = (((float)image.pixels[pos.v][pos.u].b / 255.0f) * 2.0f) - 1.0f;

	return (unit_vec3(normal));
}



t_vec3	perturb_normal(t_vec3 normal, t_vec3 perturb)
{
	t_vec3 new_up;
	t_vec3 pV;
	t_vec3 pU;

	t_vec3 res;
	//Find tangent axis for normal using cross product
	if (normal.y > 0.99f || normal.y < -0.99f)		/* If y value too close to 1 or -1 use                                                                         */
		new_up = vec3(1,0,0);
	else
		new_up = vec3(0,0,-1);

	pV = unit_vec3(cross_vec3(new_up, normal));				/* Find first axis */
	pU = unit_vec3(cross_vec3(normal, pV));				/* Find second axis */

	/* Find perturbation values from normal map vector */
	res = add_vec3(normal, mult_vec3(pU, perturb.x));
	res = add_vec3(res, mult_vec3(pV, perturb.y));
	res = add_vec3(res, mult_vec3(normal, perturb.z));
	res = unit_vec3(res);

	return (res);
}

//Code to place in render to enable texture and normal map

/* Apply texture*/
// rec->color = pattern_at_image(sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->earth, T_SPH); //For applying texture to sphere
/* Apply normal */
// rec->normal = perturb_normal(rec->normal, normal_image_to_vec3(uv_at(sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->earth_normal, T_SPH), rt->earth_normal.image));



/* How to apply bump mapping:

	1. For each point, find UV coords.
	2. Use UV coords to find point on 2d bum pmap image.
	3. By check the difference between the pixel to the right of current pixel,
		and the pixel below current pixel, we can get values to perturb the normal.






	- Read in a png file, and rip the relevant pixel data into and array
	- Use UV coords to access the correct element of the array
	- Read normal data from the pixel element
	- Add together the original normal and normal perturbation to get new normal.





		https://pathtracing.home.blog/bump-mapping/
		https://learnopengl.com/Advanced-Lighting/Normal-Mapping
*/