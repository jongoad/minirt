#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

double hit_sphere_slow(t_vec3 *sp_center, double radius2, t_ray_vec3 *r) {
    t_vec3	oc;
    double	a;
    double	b;
    double	c;
    double	discriminant;

	oc = sub_vec3(r->orig, *sp_center);
	a = dot_vec3(r->dir, r->dir);
	b = 2.0F * dot_vec3(oc, r->dir);
	c = dot_vec3(oc, oc) - radius2;
	discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return -1.0F;
	return (-b - sqrtf(discriminant) ) / (2.0F * a); 
	// Only return the smallest value, i.e. the closest
}

double hit_sphere(t_vec3 *sp_center, double radius2, t_ray_vec3 *r) {
    t_vec3	oc;
    double	a;
    double	half_b;
    double	c;
    double	discriminant;

	oc = sub_vec3(r->orig, *sp_center);
	a = dot_vec3(r->dir, r->dir);
	half_b = dot_vec3(oc, r->dir);
	c = dot_vec3(oc, oc) - radius2;
	discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return -1.0F;
	return (-half_b - sqrtf(discriminant) ) / a; 
	// Only return the smallest value, i.e. the closest
}

int		ray_color_sphere_shaded(t_ray_vec3 *r, t_vec3 sp_center)
{
	double	radius2 = 0.5F * 0.5F;
	double	t = hit_sphere(&sp_center, radius2, r);


	static t_vec3	z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3	unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
    t_vec3			unit_direction;
	t_vec3			color;

    if (t > 0.0F)
	{
		// ray.at(t) == orig + t * dir
		color = add_vec3(r->orig, mult_vec3(r->dir, t) );
		color = unit_vec3(sub_vec3(color, z_norm));
		color = add_vec3(color, unit);
		color = mult_vec3(color, 127.999F); // 0.5F * 255
        return (vec3_to_color(&color));
	}

	/* Black background */
	// return (WHITE);

	/* Funky background */
	static double	h_divider = 1.0f / (IMG_H - 1);
    static double	w_divider = 1.0f / (IMG_W - 1);


	unit_direction = unit_vec3(r->dir);
	color.x = 255.0F * fabs(unit_direction.x * 255) * w_divider;
	color.y = 255.0F * fabs(unit_direction.y * 255) * h_divider;
	color.z = 64.0F;
    return vec3_to_color(&color);

	/* White/blue shade background */
	// static t_vec3	grad1 = { .x = 1.0, .y = 1.0, .z = 1.0 };
	// static t_vec3	grad2 = { .x = 0.5, .y = 0.7, .z = 1.0 };

	// unit_direction = unit_vec3(r->dir);
	// t = 0.5F * (unit_direction.y + 1.0F);
	// color = mult_vec3(grad1, 1.0F - t);
	// color = add_vec3(color, mult_vec3(grad2, t));
	// color = mult_vec3(color, 255);
    // return vec3_to_color(&color);
}

void	generate_sphere_shaded(t_data *rt, t_vec3 *sp_center)
{

    // Image
    double	aspect_ratio = 16.0 / 9.0;
    int		image_width = IMG_W;
    int		image_height = (int)(image_width / aspect_ratio);

    // Camera
    double viewport_height = 2.0F;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0F;

    t_vec3 origin = vec3(0, 0, 0);
    t_vec3 horizontal = vec3(-viewport_width, 0, 0);
    t_vec3 vertical = vec3(0, -viewport_height, 0);
    t_vec3 lower_left_corner = sub_vec3(origin, div_vec3(horizontal, 2));
	lower_left_corner = sub_vec3(lower_left_corner, div_vec3(vertical, 2));
	lower_left_corner = sub_vec3(lower_left_corner, vec3(0, 0, focal_length));

	// lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
	t_ray_vec3	r;
	t_vec3		destination;
	int			pixel_color;
	double		u;
	double		v;


	double	start_time = (double)clock();

	r.orig = origin;

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            u = (double)(i) / (image_width-1);
            v = (double)(j) / (image_height-1);
			destination = sub_vec3(add3_vec3(
				lower_left_corner,
				mult_vec3(horizontal, u),
				mult_vec3(vertical, v)),
				origin);
			r.dir = destination;
            pixel_color = ray_color_sphere_shaded(&r, *sp_center);
			// printf("%d %d : %d %d %d\n", i, j, (pixel_color >> 16), (pixel_color >> 8 & 0xFF), (pixel_color & 0xFF));
            fill_pixel(rt->img, i, j, pixel_color);
        }
    }
	double	end_time = (double)clock();
	double	time_elapsed = end_time - start_time;
	g_fps = 1000000 / time_elapsed;
	display_default(rt);

	// Display FPS
	char 	buff[10];
	char	*fps;

	snprintf(buff, 10, "%.2lf", g_fps);
	fps = ft_strjoin(buff, " fps");
	
	// Causes leaks...
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 10, RED, fps);

	free(fps);


	static uint64_t	fps_tot;
	static uint64_t	nb_inputs;

	fps_tot += (int)g_fps;
	nb_inputs++;
	
	printf("render time: %.2lf ms\n", time_elapsed / 1000);
	printf("FPS: %.2lf Avg = %llu\n", g_fps, fps_tot / nb_inputs);
}