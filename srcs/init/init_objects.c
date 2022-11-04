#include "minirt.h"

/* Initialize ambient light object using parsed input data */
void	init_ambient(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	/*FIXME - Replace with non library string to float function */
	rt->ambient.ratio = atof(input[1]);
	init_color(&rt->ambient.clr, input[2]);
	rt->ambient.scene_ambient 
		= mult_vec3(color_to_vec3(rt->ambient.clr), rt->ambient.ratio / 255);
} 

/* Initilize camera object using parsed input data */
void	init_camera(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	init_float_triplet(&rt->cam.pos, input[1]);					/* Init camera position */
	init_float_triplet(&rt->cam.forward, input[2]);				/* Init camera orientation */
	rt->cam.fov = ft_atoi(input[3]);							/* Init camera FOV */
}

/* Initialize light object using parsed input data */
void	init_light(t_data *rt, char **input, int obj_nb)
{
	rt->lights[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->lights[obj_nb]->type = T_LIGHT;
	init_float_triplet(&rt->lights[obj_nb]->pos, input[1]);		/* Init light position */
	rt->lights[obj_nb]->ratio = atof(input[2]);					/* Init brightness ratio */
	if (BONUS == 0)
		init_color(&rt->lights[obj_nb]->clr, "255,255,255"); 	/* Init light colour for bonus */
	else
		init_color(&rt->lights[obj_nb]->clr, input[3]); 		/* Init light colour for bonus */
}

/* Initialize bonus properties for objects */
void	init_obj_bonus(t_obj *obj, char *shininess, char *texture, char *normal)
{
	/* Init shininess */
	obj->shininess = atof(shininess);

	/* Init texture */
	obj->texture.is_checkers = false;
	obj->texture.is_image = false;	
	if (!ft_strcmp(texture, "checkers"))
	{
		if (obj->type == T_SPH)
			obj->texture = uv_checkers(16, 8, int_to_color(BLACK), int_to_color(WHITE));
		else
			obj->texture = uv_checkers(8, 8, int_to_color(BLACK), int_to_color(WHITE));
	}
	else if (ft_strcmp(texture, "n/a/"))
	{
		if (read_ppm(&obj->texture.image, texture))
		{
			obj->texture.is_image = true;
			obj->texture.width = obj->texture.image.width;
			obj->texture.height = obj->texture.image.height;
		}
	}

	/* Init normal map */
	obj->normal.is_image = false;
	obj->normal.is_checkers = false;
	if (ft_strcmp(normal, "n/a"))   /* Only attempt to read normal if not n/a*/
	{
		if (read_ppm(&obj->normal.image, normal))
		{
			obj->normal.is_image = true;
			obj->normal.width = obj->normal.image.width;
			obj->normal.height = obj->normal.image.height;
		}
	}

}

/* Initialize plane object using parsed input data */
void	init_plane(t_data *rt, char **input, int obj_nb)	
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_PLANE;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);		/* Init plane position */
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);		/* Init plane orientation */
	init_color(&rt->objs[obj_nb]->clr, input[3]);				/* Init plane color */
	rt->objs[obj_nb]->hit = hit_plane;
	if (BONUS)
		init_obj_bonus(rt->objs[obj_nb], input[4], input[5], input[6]);
	rt->objs[obj_nb]->rot = vec3(0,0,0);
}


/* Initialize sphere object using parsed input data */
void	init_sphere(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_SPH;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);		/* Init sphere position */
	rt->objs[obj_nb]->radius = atof(input[2]) / 2;				/* Init sphere radius */
	init_color(&rt->objs[obj_nb]->clr, input[3]);				/* Init sphere color */
	rt->objs[obj_nb]->hit = hit_sphere;
	if (BONUS)
		init_obj_bonus(rt->objs[obj_nb], input[4], input[5], input[6]);
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->rot = vec3(0,0,0);
}

/* Initialize cylinder object using parsed input data */
void	init_cylinder(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));			/* Allocate object */
	rt->objs[obj_nb]->type = T_CYL;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);	/* Init cylinder position */
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);	/* Init cylinder orientation */
	unit_vec3_self(&rt->objs[obj_nb]->fwd);					/* Normalize cylinder orientation */
	rt->objs[obj_nb]->radius = atof(input[3]) / 2;			/* Init cylinder radius */
	rt->objs[obj_nb]->half_height = atof(input[4]);			/* Init cylinder height */
	rt->objs[obj_nb]->half_height /= 2;						/* Only (height / 2) is used */
	init_color(&rt->objs[obj_nb]->clr, input[5]);			/* Init cylinder color */
	rt->objs[obj_nb]->hit = hit_cylinder;
	if (BONUS)
		init_obj_bonus(rt->objs[obj_nb], input[6], input[7], input[8]);
	rt->objs[obj_nb]->rot = vec3(0,0,0);
}
//REMOVED THIS CODE FROM CYLINDER, CHECK WITH ISMAEL
// t_obj	*o;
// Added by Ismael, to test local_to_world matrices;
// o = rt->objs[obj_nb];
// o->right = unit_vec3(cross_vec3(o->fwd, vec3(0, 1, 0)));
// o->up = unit_vec3(cross_vec3(o->fwd, o->right));
// o->l_to_w = mat4(vec3_to_vec4(o->right, T_VEC), vec3_to_vec4(o->fwd, T_VEC),
// 	vec3_to_vec4(o->up, T_VEC), (t_vec4){0, 0, 0, 1});
// o->w_to_l = mat_inv(o->l_to_w, 4);
	/* Turn this on to test for cones */
// rt->objs[obj_nb]->hit = hit_cone;

void	init_cone(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));			/* Allocate object */
	rt->objs[obj_nb]->type = T_CONE;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);	/* Init cone position */
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);	/* Init cone orientation */
	unit_vec3_self(&rt->objs[obj_nb]->fwd);					/* Normalize cone orientation */
	rt->objs[obj_nb]->angle = atof(input[3]);				/* Init cone angle */
	rt->objs[obj_nb]->half_height = atof(input[4]);			/* Init cone height */
	rt->objs[obj_nb]->half_height /= 2;						/* Only (height / 2) is used */
	init_color(&rt->objs[obj_nb]->clr, input[5]);			/* Init cone color */
	rt->objs[obj_nb]->hit = hit_cone;
	if (BONUS)
		init_obj_bonus(rt->objs[obj_nb], input[6], input[7], input[8]);
	rt->objs[obj_nb]->rot = vec3(0,0,0);
}