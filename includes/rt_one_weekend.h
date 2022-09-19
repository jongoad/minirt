#ifndef MINIRT_RT_ONE_WEEKEND_H
# define MINIRT_RT_ONE_WEEKEND_H

double	g_fps;

typedef struct s_data		t_data;
typedef struct s_ray_vec3	t_ray_vec3;
typedef struct s_vec3		t_vec3;

void    hello_world(t_data *rt);
void	generate_background(t_data *rt);
void	generate_sphere_simple(t_data *rt);
void	generate_sphere_shaded(t_data *rt, t_vec3 *sp_center);
void	generate_sphere_shaded_new(t_data *rt, t_vec3 *sp_center); // To test if it is faster by copyt

#endif // MINIRT_RT_ONE_WEEKEND_H
