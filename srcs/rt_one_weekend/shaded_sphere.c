#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

static inline t_vec3    vec3(double x, double y, double z)
{
    t_vec3  v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

/**
 * @brief 
 * 
 * @param center 
 * @param radius 
 * @param r 
 * @return double 
 */
double hit_sphere(t_vec3 *center, double radius2, t_ray_vec3 *r) {
    t_vec3	oc;
    double	a;
    double	b;
    double	c;
    double	discriminant;

	oc = sub_vec3(r->orig, *center);
	a = dot_vec3(r->dir, r->dir);
	b = 2.0F * dot_vec3(oc, r->dir);
	c = dot_vec3(oc, oc) - radius2;
	discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return -1.0F;
	return (-b - sqrt(discriminant) ) / (2.0F * a); 
	// Only return the smallest value, i.e. the closest
}

int		ray_color_sphere_shaded(t_ray_vec3 *r)
{
	t_vec3	center = vec3(0,0,-1);
	double	radius2 = 0.5F * 0.5F;
	double	t = hit_sphere(&center, radius2, r);


	static t_vec3	grad1 = { .x = 1.0, .y = 1.0, .z = 1.0 };
	static t_vec3	grad2 = { .x = 0.5, .y = 0.7, .z = 1.0 };
	static t_vec3	z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3	unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
    t_vec3			unit_direction;
	t_vec3			color;

    if (t > 0.0F)
	{
		color = add_vec3(r->orig, mult_vec3(r->dir, t) );
		color = unit_vec3(sub_vec3(color, z_norm));
		color = add_vec3(color, unit);
		color = mult_vec3(color, 127.999F); // 0.5F * 255
        return (vec3_to_color(&color));
	}

	unit_direction = unit_vec3(r->dir);
	t = 0.5F * (unit_direction.y + 1.0F);
	color = mult_vec3(grad1, 1.0F - t);
	color = add_vec3(color, mult_vec3(grad2, t));
	color = mult_vec3(color, 255);
    return vec3_to_color(&color);
}

// color ray_color(const ray& r) {
//     auto t = hit_sphere(point3(0,0,-1), 0.5, r);
//     if (t > 0.0) {
//         vec3 N = unit_vector(r.at(t) - vec3(0,0,-1)); // at ==  orig + t*dir;
//         return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
//     }
//     vec3 unit_direction = unit_vector(r.direction());
//     t = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
// }

void	generate_sphere_shaded(t_data *rt)
{

    // Image
    double	aspect_ratio = 16.0 / 9.0;
    int		image_width = IMG_W;
    int		image_height = (int)(image_width / aspect_ratio);

	printf("image_width = %d\n", image_width);
	printf("image_height = %d\n", image_height);

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

    // Render

	printf("P3\n%d %d\n", image_width, image_height);

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
            pixel_color = ray_color_sphere_shaded(&r);
			// printf("%d %d : %d %d %d\n", i, j, (pixel_color >> 16), (pixel_color >> 8 & 0xFF), (pixel_color & 0xFF));
            fill_pixel(rt->img, i, j, pixel_color);
        }
    }
	double	end_time = (double)clock();
	display_default(rt);


	double	time_elapsed = end_time - start_time;


	printf("time elapsed: %.2lf us\n", time_elapsed);
}