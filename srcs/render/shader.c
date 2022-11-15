/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 14:18:36 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_shader
{
	t_ray		pt_to_l;
	t_hit_rec	rec;
	t_color		ambient;
	t_vec3		light_dir;
	t_vec3		p_to_l;
	t_vec3		view_dir;
	t_vec3		half_dir;
	t_vec3		light_color;
	double		dist;
	double		specular;
	double		spec_angle;
	double		lambertian;
}	t_shader;

static inline t_color	apply_diffuse(t_shader *shader, t_hit_rec *rec)
{
	return (color_x_vec3(rec->color, \
		mult_vec3(\
			shader->light_color, \
			shader->lambertian * KD / shader->dist)));
}

static inline t_color	apply_specular(t_shader *shader, t_obj *light)
{
	return (mult_color(light->clr, shader->specular * KS / shader->dist));
}

static inline bool	calculate_shader_vars(
		t_data *rt, t_hit_rec *rec, t_shader *shader, t_obj *light)
{
	shader->pt_to_l.orig = rec->p;
	shader->pt_to_l.dir = sub_vec3(light->pos, rec->p);
	if (dot_vec3(shader->pt_to_l.dir, rec->normal) <= 0.0F)
		return (false);
	shader->dist = length_vec3(shader->pt_to_l.dir);
	shader->rec.t = shader->dist;
	unit_vec3_self(&shader->pt_to_l.dir);
	if (hit_anything(rt, &shader->pt_to_l, &shader->rec) \
		&& fabs(shader->rec.t - shader->dist) > EPSILON)
		return (false);
	shader->dist += 1.0F;
	shader->dist *= shader->dist;
	shader->light_color = div_vec3(color_to_vec3(light->clr), 255);
	shader->lambertian = fmax(dot_vec3(shader->pt_to_l.dir, rec->normal), 0);
	shader->light_dir = shader->pt_to_l.dir;
	shader->view_dir = unit_vec3(sub_vec3(rt->cam.pos, shader->pt_to_l.orig));
	shader->half_dir = unit_vec3(add_vec3(shader->light_dir, shader->view_dir));
	shader->spec_angle = fmax(dot_vec3(shader->half_dir, rec->normal), 0.0F);
	shader->specular = pow(shader->spec_angle, rec->obj->shininess);
	return (true);
}

/** 
 * 	Code for illumination found at:
 *  https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
 */
t_color	pixel_shader(t_data *rt, t_hit_rec *rec, t_color color)
{
	static t_shader	shader;
	int				i;

	color = color_x_vec3(color, rt->ambient.scene_ambient);
	color.r = pow(color.r, 0.9F);
	color.g = pow(color.g, 0.9F);
	color.b = pow(color.b, 0.9F);
	i = -1;
	while (++i < rt->nb_lights)
	{
		if (calculate_shader_vars(rt, rec, &shader, rt->lights[i]) == false)
			continue ;
		color = add_color(color, apply_diffuse(&shader, rec));
		if (rt->toggle.is_specular)
			color = add_color(color, apply_specular(&shader, rt->lights[i]));
	}
	return (color);
}
