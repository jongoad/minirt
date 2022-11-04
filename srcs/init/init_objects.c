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
	if (BONUS && input[3])
		init_color(&rt->lights[obj_nb]->clr, input[3]); 		/* Init light colour for bonus */
	else
		init_color(&rt->lights[obj_nb]->clr, "255,255,255"); 	/* Init default light colour */
}

/* Load and initialize texture from image*/
void	init_texture(t_obj *obj, char *input)
{
	obj->texture.is_image = false;
	obj->texture.is_checkers = false;
	if (!ft_strcmp(input, "checkers"))
	{
		if (obj->type == T_SPH)
			obj->texture = uv_checkers(16, 8, int_to_color(BLACK), int_to_color(WHITE));
		else
			obj->texture = uv_checkers(8, 8, int_to_color(BLACK), int_to_color(WHITE));
	}
	else if (read_ppm(&obj->texture.image, input))
	{
		obj->texture.is_image = true;
		obj->texture.width = obj->texture.image.width;
		obj->texture.height = obj->texture.image.height;
	}
}

/* Load and initialize normal map from image */
void	init_normal(t_obj *obj, char *input)
{
	obj->normal.is_image = false;
	if (read_ppm(&obj->normal.image, input))
	{
		obj->normal.is_image = true;
		obj->normal.width = obj->normal.image.width;
		obj->normal.height = obj->normal.image.height;
	}
}

/* Initialize bonus properties for objects */
void	init_obj_bonus(t_obj *obj, char **input)
{
	char	**split;
	t_i		i;

	i.x = 0;
	while (input[i.x])
	{
		split = ft_split(input[i.x], ':');
		if (split[0] && split[1])
		{
			if (!ft_strcmp(split[0], "texture"))
				init_texture(obj, split[1]);
			else if (!ft_strcmp(split[0], "normal"))
				init_normal(obj, split[1]);
			else if (!ft_strcmp(split[0], "shininess"))
				obj->shininess = atof(split[1]);
			else
				obj->shininess = SHININESS;
		}
		ft_free_split(split);
		i.x++;
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
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->shininess = SHININESS;
	if (BONUS && input[4])
		init_obj_bonus(rt->objs[obj_nb], &input[4]);
	else
	{
		rt->objs[obj_nb]->texture.is_image = false;
		rt->objs[obj_nb]->texture.is_checkers = false;
		rt->objs[obj_nb]->normal.is_image = false;
	}
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
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->shininess = SHININESS;
	if (BONUS && input[4])
		init_obj_bonus(rt->objs[obj_nb], &input[4]);
	else
	{
		rt->objs[obj_nb]->texture.is_image = false;
		rt->objs[obj_nb]->texture.is_checkers = false;
		rt->objs[obj_nb]->normal.is_image = false;
	}
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
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->shininess = SHININESS;
	if (BONUS && input[6])
		init_obj_bonus(rt->objs[obj_nb], &input[6]);
	else
	{
		rt->objs[obj_nb]->texture.is_image = false;
		rt->objs[obj_nb]->texture.is_checkers = false;
		rt->objs[obj_nb]->normal.is_image = false;
	}
}

/* Initialize cone object using parsed data */
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
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->shininess = SHININESS;
	if (BONUS && input[6])
		init_obj_bonus(rt->objs[obj_nb], &input[6]);
	else
	{
		rt->objs[obj_nb]->texture.is_image = false;
		rt->objs[obj_nb]->texture.is_checkers = false;
		rt->objs[obj_nb]->normal.is_image = false;
	}
}