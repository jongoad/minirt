#ifndef MINIRT_RT_ONE_WEEKEND_H
# define MINIRT_RT_ONE_WEEKEND_H

extern double	g_fps;

typedef struct s_data		t_data;
typedef struct s_ray_vec3	t_ray_vec3;
typedef struct s_vec3		t_vec3;
typedef struct s_obj		t_obj;

void    hello_world(t_data *rt);
void	generate_background(t_data *rt);
void	generate_sphere_simple(t_data *rt);

void	generate_sphere_shaded(t_data *rt, t_obj *sp);

/* Objects */
t_obj	*get_sphere( );

/* Benchmarking */
void	display_fps(t_data *rt, double start_time);

#endif // MINIRT_RT_ONE_WEEKEND_H
