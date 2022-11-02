#include "minirt.h"

/* Function to create a checkerboard pattern */
t_texture uv_checkers(int width, int height, t_color c1, t_color c2)
{
	t_texture res;

	res.width = width;
	res.height = height;
	res.c1 = c1;
	res.c2 = c2;
	res.is_image = false;
	return (res);
}

/* Return color at a given uv coordinate */
t_color uv_pattern_at_checkers(t_texture texture, t_vec2 uv)
{
	int u2;
	int v2;

	u2 = floor(uv.u * texture.width);
	v2 = floor(uv.v * texture.height);

	if ((u2 + v2) % 2 == 0)
		return (texture.c1);
	else
		return (texture.c2);
}

/* Get colour value from image based on UV coord */
// t_color uv_pattern_at_image(t_texture texture, t_vec2 uv)
// {
// 	unsigned int	u2;
// 	unsigned int	v2;

// 	u2 = floor((1.0f - uv.u) * texture.width);
// 	v2 = floor((1.0f - uv.v) * texture.height);
// 	return (texture.image.pixels[v2][u2]);
// }

t_color uv_pattern_at_image(t_texture texture, float u, float v)
{
	//1 - value is to invert texture
	int	u2 = floor( (1 - u) * texture.width);

	int	v2 = floor( (1 - v) * texture.height);


	t_color ret = texture.image.pixels[v2][u2];
	return (ret);
}


/* Get proper color value from a texture for a given point */
t_color	obj_get_color(t_data *rt, t_vec3 p, t_obj *obj)
{
	t_vec2	uv;

	if (rt->toggle.is_texture)
	{
		if (obj->type == T_SPH)
			uv = spherical_map(p);
		else if (obj->type == T_PLANE)
			uv = planar_map(p);
		else if (obj->type == T_CYL)
			uv = cylindrical_map(p);
	}
	if (rt->toggle.is_texture && obj->texture.is_image)
		return(uv_pattern_at_image(obj->texture, uv.u, uv.v));
	else if (rt->toggle.is_texture && obj->texture.is_checkers)
		return(uv_pattern_at_checkers(obj->texture, uv));
	else
		return(obj->clr);
}



// t_color uv_pattern_at_image(t_texture texture, float u, float v)
// {
// 	//1 - value is to invert texture
// 	int	u2 = floor( (1 - u) * texture.width);

// 	int	v2 = floor( (1 - v) * texture.height);


// 	t_color ret = texture.image.pixels[v2][u2];
// 	return (ret);
// }


// t_color pattern_at(t_vec3 p, t_texture texture, char type)
// {
// 	t_vec2 uv;

// 	if (type == T_SPH)
// 		uv = spherical_map(p);
// 	else if (type == T_PLANE)
// 		uv = planar_map(p);
// 	else if (type == T_CYL)
// 		uv = cylindrical_map(p);
// 	return (uv_pattern_at(texture, uv.u, uv.v));
// }

// t_uv uv_at(t_vec3 p, t_texture texture, char type)
// {
// 	t_vec2	uv;
// 	t_uv	res;
// 	if (type == T_SPH)
// 		uv = spherical_map(p);
// 	else if (type == T_PLANE)
// 		uv = planar_map(p);
// 	else if (type == T_CYL)
// 		uv = cylindrical_map(p);

// 	res.u = floor((1.0f - uv.u) * texture.width);
// 	res.v = floor((1.0f - uv.v) * texture.height);
// 	return (res);
// }

// /* Get colour for non-image texture */
// t_color pattern_at(t_vec3 p, t_texture texture, char type)
// {
// 	t_vec2 uv;

// 	if (type == T_SPH)
// 		uv = spherical_map(p);
// 	else if (type == T_PLANE)
// 		uv = planar_map(p);
// 	else if (type == T_CYL)
// 		uv = cylindrical_map(p);
// 	return (uv_pattern_at(texture, uv.u, uv.v));
// }

// /* Get colour for image texture */
// t_color pattern_at_image(t_vec3 p, t_texture texture, char type)
// {
// 	t_vec2 uv;

// 	if (type == T_SPH)
// 		uv = spherical_map(p);
// 	else if (type == T_PLANE)
// 		uv = planar_map(p);
// 	else if (type == T_CYL)
// 		uv = cylindrical_map(p);
// 	return (uv_pattern_at_image(texture, uv.u, uv.v));
// }

/* Get texture colour for current object */

/* To-do:
	- Properly apply inverse rotation and translation to each object before calculating uv
		- Not sure if this matters for planes, but def matters for cylinder and sphere
		- Rotation does not seem to matter for planes
	- Embed each texture inside object
	- Figure out where to call the uv mapping function from
	- Remove t_vec2 and just use vec3 instead
*/
