#ifndef MINIRT_H
# define MINIRT_H

/****************************/
/*         Includes         */
/****************************/

/* System Includes */
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>


/* Library Includes */
// # include "../minilibx_opengl/mlx_opengl.h"
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"

/* Local File Includes */
# include "rt_one_weekend.h"
# include "structs.h"
# include "defines_enums.h"
# include "error.h"


/*******************************/
/*    Function Declarations    */
/*******************************/


/* Initialization */
void	rt_init(t_data *rt, char *filepath);

/* Hooks */
void	set_hooks(t_data *rt);

/* Objects */
t_obj	*new_sphere( t_vec3 center, float radius, t_vec3 color );
t_obj	*new_plane(t_vec3 center, t_vec3 normal, t_vec3 color);
t_obj	*new_cylinder(t_vec3 center, t_vec3 normal, float diameter, float height, t_vec3 color);

/* Object intersection functions */
bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);
bool	hit_sphere_no_hit_rec(t_ray_vec3 *r, t_obj *o);
bool	hit_plane(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);
bool	hit_cylinder(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);


/* Colors */
int		int_to_color(int r, int g, int b);
void    color(t_color *c);
int     vec3_to_color(t_vec3 c);
int     vec3_to_color_copy(t_vec3 c);
t_vec3	color_to_vec3(int c);


/* Display */
int	display_default(t_data *rt);
int	display_img(t_data *rt, t_img *img);


/* Ray Generation */
t_vec3		*init_pixel_point(t_data *data, int x, int y);



t_data		*get_data(void);

int	cast_ray_at_pixel(t_data *rt, int x, int y); //FIXME: added by ismael


/* Matrix functions */
float	**matrix_identity(int fill, int fill_diagonal);
float	**matrix_rotation(float x, char axis);
float	**matrix_scale(t_vec3 scale);
float	**matrix_translate(t_vec3 translate);
float	**matrix_mult_mat(float **m1, float **m2);
void	matrix_mult_point(t_vec3 *v, float **mat);
void	matrix_free(float **mat);

/* Utils */
void	*ft_xalloc(size_t size);
void	exit_on_err(char *err_message);
void	draw_background(t_img *img, int color);
void	fill_pixel(t_img *img, int x, int y, int color);
double	lerp(double start, double end, double curr);
int		lerp_color(int start, float ratio);

/* Cleanup */
int		rt_clean_exit(t_data *rt);
void	rt_cleanup(t_data *rt);




/* Vectors by copy */
t_vec3	vec3(double x, double y, double z);
t_vec3	add_vec3(t_vec3 a, t_vec3 b);
t_vec3	add3_vec3(t_vec3 a, t_vec3 b, t_vec3 c);
double	dot_vec3(t_vec3 a, t_vec3 b);
t_vec3	sub_vec3(t_vec3 a, t_vec3 b);
t_vec3	mult_vec3_vec3(t_vec3 a, t_vec3 b);
t_vec3	mult_vec3(t_vec3 v, double b);
t_vec3	div_vec3(t_vec3 v, double b);
double	length_vec3(t_vec3 v);
t_vec3	unit_vec3(t_vec3 v);
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);
t_vec3	negate_vec3(t_vec3 v);
t_vec3	lerp_vec3( t_vec3 a, t_vec3 b, float factor );
t_vec3  mean_vec3( t_vec3 a, t_vec3 b );
double	cos_vec3(t_vec3 a, t_vec3 b);

/* Vectors self-operations */
void	add_vec3_self(t_vec3 *a, t_vec3 b);
void	add3_vec3_self(t_vec3 *a, t_vec3 b, t_vec3 c);
void	sub_vec3_self(t_vec3 *a, t_vec3 b);
void	mult_vec3_vec3_self(t_vec3 *a, t_vec3 b);
void	mult_vec3_self(t_vec3 *v, double b);
void	div_vec3_self(t_vec3 *v, double b);
void	unit_vec3_self(t_vec3 *v);
void	cross_vec3_self(t_vec3 *a, t_vec3 b);
void	negate_vec3_self(t_vec3 *v);




// Camera testing
t_vec3	mat_mult_vec3(t_vec3 *v, float **mat);











/* Matrix functions MOVED FROM RT */
// float	**mat_id(int fill, int fill_diagonal);
// float	**mat_rot(float x, char axis);
// float	**mat_scale(t_point scale);
// float	**mat_trans(t_point translate);
// float	**mat_mult_mat(float **m1, float **m2);
// void	mat_mult_vec4(t_point *v, float **mat);
// void	mat_free(float **mat);




/* Parsing Functions */
void	init_parse(t_parse *dat);
int		open_scene(t_parse *dat, char *path);
int		check_tok(char *input, char** tok);
int		check_scene(t_parse *dat);
int		parse(t_data *rt, char *path);

/* Individual Object Parsing Functions */
int		parse_ambient(char **obj);
int		parse_camera(char **obj);
int		parse_light(char **obj);
int		parse_plane(char **obj);
int		parse_sphere(char **obj);
int		parse_cylinder(char **obj);

/* Parsing Utils */
int 	check_rgb(char *rgb);
int		check_float(char *val, float lim1, float lim2);
int		check_int(char *val, int lim1, int lim2);
int		check_orientation(char *orient);
int		check_coords(char *coord);
void	replace_whitespace(t_parse *dat);

/* Scene Initialization Functions */
void	init_scene(t_data *rt);
void	init_scene_init(t_data *rt);
void	count_objects(t_data *rt);
void	init_color(t_color *clr, char *input);
void	init_float_triplet(t_vec3 *vec, char *input);
void	init_ambient(t_data *rt, char **input, int obj_nb);
void	init_camera(t_data *rt, char **input, int obj_nb);
void	init_light(t_data *rt, char **input, int obj_nb);
void	init_plane(t_data *rt, char **input, int obj_nb);
void	init_sphere(t_data *rt, char **input, int obj_nb);
void	init_cylinder(t_data *rt, char **input, int obj_nb);


#endif // MINIRT_H