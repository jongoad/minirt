#include "minirt.h"












/* Apply transforms to sphere */
void apply_transform_sp(t_data *rt, t_obj *cur)
{
	float **mat;
	t_vec3 res;

	cur->c_radius = cur->radius * cur->scale;			/* Apply scale to radius */
	mat = matrix_translate(cur->trans);					/* Apply translation to origin point */
	res = mat_mult_vec3(&cur->center, mat);

	cur->c_center.x = res.x;
	cur->c_center.y = res.y;
	cur->c_center.z = res.z;
}


/* Apply current transforms to each object */
void	apply_transform_obj(t_data *rt)
{
	t_i i;

	i.x = 0;
	while (i.x < rt->nb_objs)
	{
		//Call correct transform function to apply transform to avoid using if/else statements
		i.x++;
	}
}

/* Apply camera transform to each object in scene */
void	apply_transform_cam()
{

}

/* Calculate inverse matrices to apply camera transform to scene */
void	calculate_transform_cam()
{

}
