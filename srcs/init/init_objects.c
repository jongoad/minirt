#include "minirt.h"

/*	Position matrix init steps:

	Assume provided orientation vector points down the z axis for the object in local space 

	Given a vector:

		Tv = {1, 1, -1}
	
	Need to find how much the object needs to be rotated on each axis to make its z unit vector equal to this?

	mat3 rotation_matrix(vec3 v)

   // Find cosφ and sinφ 
    float c1 = sqrt(v.x * v.x + v.y * v.y);
    float s1 = v.z;
   // Find cosθ and sinθ; if gimbal lock, choose (1,0) arbitrarily
    float c2 = c1 ? v1.x / c1 : 1.0;
    float s2 = c1 ? v1.y / c1 : 0.0;

    return mat3(v.x, -s2, -s1*c2,
                v.y,  c2, -s1*s2,
                v.z,   0,     c1);


*/


/* Initilize coord/orientation matrix for object */
void	init_mat_obj(t_obj *obj)
{
	mat_id(&obj->p);

}

/* Initilize coord/orientation matrix for camera */
void	init_mat_cam(t_camera *cam)
{
	mat_id(&cam->p);
}

/* Split a colour input into components */
void	init_color(t_color *clr, char *input)
{
	char **split;

	split = ft_split(input, ',');
	clr->r = ft_atoi(split[0]);
	clr->g = ft_atoi(split[1]);
	clr->b = ft_atoi(split[2]);
	clr->weight = 1;
	ft_free_split(split);
}

/* Initialize a vec3 from parsed input data */
void	init_float_triplet(t_vec3 *vec, char *input)
{
	/* FIXME - Replace string to float with non library version */
	char **split;

	split = ft_split(input, ',');
	vec->x = atof(split[0]);
	vec->y = atof(split[1]);
	vec->z = atof(split[2]);

}

/* Initialize ambient light object using parsed input data */
void	init_ambient(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	/*FIXME - Replace with non library string to float function */
	rt->ambient.ratio = atof(input[1]);
	init_color(&rt->ambient.clr, input[2]);
} 

/* Initilize camera object using parsed input data */
void	init_camera(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	init_float_triplet(&rt->cam.pos, input[1]);					/* Init camera position */
	init_float_triplet(&rt->cam.aim, input[2]);					/* Init camera orientation */
	rt->cam.fov = ft_atoi(input[3]);							/* Init camera FOV */

	// FIXME: Ish's crumpled up mess of a camera init
    rt->cam.view_h = 1.0F;
    rt->cam.view_w = ASPECT_RATIO * rt->cam.view_h;
    rt->cam.z_offset = 1.0F;
    rt->cam.pos = vec3(0, 0, 0);
    rt->cam.horizontal = vec3(-rt->cam.view_w, 0, 0);
    rt->cam.vertical = vec3(0, -rt->cam.view_h, 0);
    rt->cam.low_left = sub_vec3(rt->cam.pos, div_vec3(rt->cam.horizontal, 2));
	sub_vec3_self(&(rt->cam.low_left), div_vec3(rt->cam.vertical, 2));
	sub_vec3_self(&(rt->cam.low_left), vec3(0, 0, rt->cam.z_offset));
	init_mat_cam(&rt->cam); /* Init matrix containing position and orientation data */
}

/* Initialize light object using parsed input data */
void	init_light(t_data *rt, char **input, int obj_nb)
{
	rt->lights[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->lights[obj_nb]->type = T_LIGHT;
	init_float_triplet(&rt->lights[obj_nb]->center, input[1]);	/* Init light position */
	rt->lights[obj_nb]->ratio = atof(input[2]);					/* Init brightness ratio */
	if (BONUS == 0)
		init_color(&rt->lights[obj_nb]->clr, "255,255,255"); 			/* Init light colour for bonus */
	else
		init_color(&rt->lights[obj_nb]->clr, input[3]); 			/* Init light colour for bonus */
	rt->lights[obj_nb]->color.x = rt->lights[obj_nb]->clr.r;
	rt->lights[obj_nb]->color.y = rt->lights[obj_nb]->clr.g;
	rt->lights[obj_nb]->color.z = rt->lights[obj_nb]->clr.b;
}

/* Initialize plane object using parsed input data */
void	init_plane(t_data *rt, char **input, int obj_nb)	
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_PLANE;
	init_float_triplet(&rt->objs[obj_nb]->center, input[1]);	/* Init plane position */
	init_float_triplet(&rt->objs[obj_nb]->normal, input[2]);	/* Init plane orientation */
	init_color(&rt->objs[obj_nb]->clr, input[3]);				/* Init plane color */

	//FIXME: TO REMOVE. For refactoring purposes
	rt->objs[obj_nb]->color.x = rt->objs[obj_nb]->clr.r;
	rt->objs[obj_nb]->color.y = rt->objs[obj_nb]->clr.g;
	rt->objs[obj_nb]->color.z = rt->objs[obj_nb]->clr.b;
	rt->objs[obj_nb]->hit = hit_plane;
}

/* Initialize sphere object using parsed input data */
void	init_sphere(t_data *rt, char **input, int obj_nb)
{
	/*FIXME - Replace with non library string to float function */
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_SPH;
	init_float_triplet(&rt->objs[obj_nb]->center, input[1]);	/* Init sphere position */
	rt->objs[obj_nb]->radius = atof(input[2]) / 2;				/* Init sphere radius */
	init_color(&rt->objs[obj_nb]->clr, input[3]);				/* Init sphere color */

	//FIXME: TO REMOVE. For refactoring purposes
	rt->objs[obj_nb]->color.x = rt->objs[obj_nb]->clr.r;
	rt->objs[obj_nb]->color.y = rt->objs[obj_nb]->clr.g;
	rt->objs[obj_nb]->color.z = rt->objs[obj_nb]->clr.b;
	rt->objs[obj_nb]->hit = hit_sphere;
}

/* Initialize cylinder object using parsed input data */
void	init_cylinder(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_CYL;
	init_float_triplet(&rt->objs[obj_nb]->center, input[1]);	/* Init cylinder position */
	init_float_triplet(&rt->objs[obj_nb]->normal, input[2]);	/* Init cylinder orientation */
	rt->objs[obj_nb]->radius = atof(input[3]) / 2;				/* Init cylinder radius */
	rt->objs[obj_nb]->height = atof(input[4]);				/* Init cylinder height */
	init_color(&rt->objs[obj_nb]->clr, input[5]);				/* Init cylinder color */

	//FIXME: TO REMOVE. For refactoring purposes
	rt->objs[obj_nb]->color.x = rt->objs[obj_nb]->clr.r;
	rt->objs[obj_nb]->color.y = rt->objs[obj_nb]->clr.g;
	rt->objs[obj_nb]->color.z = rt->objs[obj_nb]->clr.b;
	rt->objs[obj_nb]->hit = hit_cylinder;
}

/* Count objects for allocation and final parse step */
void	count_objects(t_data *rt)
{
	t_i	i;
	int res;

	i.x = 0;
	res = 0;
	rt->nb_objs = 0;
	rt->nb_lights = 0;
	while (rt->parse.scene[i.x])
	{
		res = check_tok(rt->parse.scene[i.x][0], rt->parse.tok);
		if (res > 2)
			rt->nb_objs++;
		else if (res == 2)
			rt->nb_lights++;
		i.x++;
	}
}

/* Setup for scene initialization */
void	init_parse_fct_ptrs(t_data *rt)
{
	rt->parse.f2[0] = init_ambient;
	rt->parse.f2[1] = init_camera;
	rt->parse.f2[2] = init_light;
	rt->parse.f2[3] = init_plane;
	rt->parse.f2[4] = init_sphere;
	rt->parse.f2[5] = init_cylinder;

}
