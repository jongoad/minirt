#include "minirt.h"

t_color apply_specular(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, t_color color, t_obj *light)
{
	double	reflect_x_view;

	// Calculate light direction and view direction.
	t_vec3 lightDirection = (r->dir);
	t_vec3 viewDirection = unit_vec3(sub_vec3(rt->cam.pos, rec->p));
	float	cosTheta = fmax(0, dot_vec3(rec->normal, unit_vec3(lightDirection)));
    
    //Only if light is visible from the surface point.
    if(cosTheta > 0) {
        
        //Reflection vector around normal.
        t_vec3 reflectionDirection = reflect_ray(lightDirection, rec->normal);
		// printf("reflectionDirection.length() = %.2f\n", length_vec3(reflectionDirection));

        reflect_x_view = dot_vec3(reflectionDirection, viewDirection);
        //Specular component.
		if (reflect_x_view > 0.0F)
		{
        	color = add_color(color, mult_color(light->clr, pow(reflect_x_view, 10) * KS));
		}
    }
    
   	return (color);

}

t_color apply_point_lights(t_data *rt, t_hit_rec *rec, t_color color)
{
	t_ray_vec3 pt_to_light;
	t_hit_rec rec2;
	double dist_to_light;
	double t;
	double h;
	int i;
	bool hit;

	hit = false;
	i = -1;
	color = color_x_vec3(color, rt->ambient.scene_ambient);
	while (++i < rt->nb_lights)
	{
		// Diffuse lighting
		pt_to_light.orig = rec->p;
		pt_to_light.dir = sub_vec3(rt->lights[i]->pos, rec->p);

		// Small optimization to fail the intersect early
		if (dot_vec3(pt_to_light.dir, rec->normal) <= 0.0F)
			continue;

		// To verify objects hits are happening before light hit
		dist_to_light = length_vec3(pt_to_light.dir);
		rec2.t = dist_to_light;
		h = length_vec3(project_a_on_b(pt_to_light.dir, rec->normal));
		unit_vec3_self(&pt_to_light.dir);
		// Test for hard shadows, correct to prevent shadow acne
		if (hit_anything(rt, &pt_to_light, &rec2) && fabs(rec2.t - dist_to_light) > EPSILON)
			continue;
		hit = true;
		t = cos_vec3(rec->normal, pt_to_light.dir);
		// t *= t;
		// t *= LIGHT_INTENSITY;
		// t /= (h + 1.0F);
		t /= (h + 1.0F);
		color = lerp_color(color, rec->color, t);
		// color = lerp_color(color, rt->lights[i]->clr, t);
		color = apply_specular(rt, &pt_to_light, rec, color, rt->lights[i]);
	}
	// return (color_x_vec3(color, rt->ambient.scene_ambient));
	// if (!hit)
	// 	return (color_x_vec3(color, rt->ambient.scene_ambient));
	return (color);
}

bool hit_light(t_ray_vec3 *r, t_obj *l, t_hit_rec *rec)
{
	l->fwd = r->dir;
	return (hit_plane(r, l, rec));
}

t_color apply_light_halos(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, t_color color)
{
	t_hit_rec rec2;
	int i;
	float dist;

	(void)rec;
	i = -1;
	while (++i < rt->nb_lights)
	{
		rec2.t = T_MAX;
		rec2.hit_anything = false;
		if (hit_light(r, rt->lights[i], &rec2))
		{
			dist = length_vec3(sub_vec3(rt->lights[i]->pos, rec2.p));
			dist += 1.0F;
			dist *= dist;
			color = lerp_color(color, rt->lights[i]->clr, 1 / dist);
		}
	}
	return (color);
}
