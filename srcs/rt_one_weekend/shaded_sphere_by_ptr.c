#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html



double hit_sphere(t_vec3 *sp_center, double radius2, t_ray_vec3_ptr *r)
{
    t_vec3	*oc;
    double	a;
    double	half_b;
    double	c;
    double	discriminant;

	oc = sub_vec3(r->orig, sp_center);
	a = dot_vec3(r->dir, r->dir);
	half_b = dot_vec3(oc, r->dir);
	c = dot_vec3(oc, oc) - radius2;
	discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return -1.0F;
	return (-half_b - sqrtf(discriminant) ) / a; 
	// Only return the smallest value, i.e. the closest
}

int		ray_color_sphere_shaded(t_ray_vec3_ptr *r, t_vec3 sp_center)
{
	double	radius2 = 0.5F * 0.5F;
	double	t = hit_sphere(&sp_center, radius2, r);

	static t_vec3	z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3	unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
    t_vec3			*unit_direction;
	// t_vec3			*color;
	t_vec3			*tmp1;
	t_vec3			*tmp2;
	int				color;

    if (t > 0.0F)
	{
		// ray.at(t) == orig + t * dir
		tmp1 = mult_vec3(r->dir, t);
		tmp2 = add_vec3(r->orig, tmp1 );
		free(tmp1);
		tmp1 = sub_vec3(tmp2, &z_norm);
		free(tmp2);
		tmp2 = unit_vec3(tmp1);
		free(tmp1);
		tmp1 = add_vec3(tmp2, &unit);
		free(tmp2);
		tmp2 = mult_vec3(tmp1, 127.999F); // 0.5F * 255
		free(tmp1);
		color = vec3_to_color(tmp2);
		free(tmp2);
        return (color);
	}

	/* Black background */
	// return (BLACK);

	/* Funky background */
	static double	h_divider = 1.0f / (IMG_H - 1);
    static double	w_divider = 1.0f / (IMG_W - 1);


	unit_direction = unit_vec3(r->dir);
	// color.x = 255.0F * fabs(unit_direction->x * 255) * w_divider;
	// color.y = 255.0F * fabs(unit_direction->y * 255) * h_divider;
	// color.z = 64.0F;
    return int_to_color(
		255.0F * fabs(unit_direction->x * 255) * w_divider,
		255.0F * fabs(unit_direction->y * 255) * h_divider,
		64.0F);

	/* White/blue shade background */
	// static t_vec3	grad1 = { .x = 1.0, .y = 1.0, .z = 1.0 };
	// static t_vec3	grad2 = { .x = 0.5, .y = 0.7, .z = 1.0 };

	// unit_direction = unit_vec3(r->dir);
	// t = 0.5F * (unit_direction.y + 1.0F);
	// color = mult_vec3(grad1, 1.0F - t);
	// color = add_vec3(color, mult_vec3(grad2, t));
	// color = mult_vec3(color, 255);
    // return new_vec3_to_color(&color);
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

    t_vec3 *origin = new_vec3(0, 0, 0);
    t_vec3 *horizontal = new_vec3(-viewport_width, 0, 0);
    t_vec3 *vertical = new_vec3(0, -viewport_height, 0);
    t_vec3 *tmp1;
    t_vec3 *tmp2;
    t_vec3 *tmp3;
    t_vec3 *low_left;
	
	
	tmp1 = div_vec3(horizontal, 2);
	tmp2 = sub_vec3(origin, tmp1);
	free(tmp1);
	tmp3 = div_vec3(vertical, 2);
	tmp1 = sub_vec3(tmp2, tmp3);
	free(tmp2);
	free(tmp3);
	tmp2 = new_vec3(0, 0, focal_length);
	low_left = sub_vec3(tmp1, tmp2);
	free(tmp1);
	free(tmp2);

	// low_left = origin - horizontal/2 - vertical/2 - new_vec3(0, 0, focal_length);

    // Render
	t_ray_vec3_ptr	r;
	t_vec3			*destination;
	int				pixel_color;
	double			u;
	double			v;


	double	start_time = (double)clock();

	r.orig = origin;
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            u = (double)(i) / (image_width-1);
            v = (double)(j) / (image_height-1);

			tmp1 = mult_vec3(horizontal, u);
			tmp2 = mult_vec3(vertical, v);
			tmp3 = add3_vec3( low_left, tmp1, tmp2 );
			free(tmp1);
			free(tmp2);
			destination = sub_vec3(tmp3, origin);
			free(tmp3);
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

	printf("render time: %.2lf ms\n", time_elapsed / 1000);
	printf("FPS: %.2lf\n", g_fps);
}