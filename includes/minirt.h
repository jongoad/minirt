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
t_data	*get_data(void);
void	rt_init(t_data *rt, char *filepath);
void	rt_init_img(t_data *rt);
void	rt_init_mlx(t_data *rt, char *filename);

/* Hooks */
void	set_hooks(t_data *rt);

/* Objects */
t_obj	*new_sphere( t_vec3 pos, float radius, t_vec3 color );
t_obj	*new_plane(t_vec3 pos, t_vec3 normal, t_vec3 color);
t_obj	*new_cylinder(t_vec3 pos, t_vec3 normal, float diameter, float height, t_vec3 color);

/* Object intersection functions */
bool	hit_sphere(t_ray *r, t_obj *o, t_hit_rec *rec);
bool	hit_sphere_no_hit_rec(t_ray *r, t_obj *o);
bool	hit_plane(t_ray *r, t_obj *o, t_hit_rec *rec);
bool	hit_cylinder(t_ray *r, t_obj *o, t_hit_rec *rec);
bool	hit_cone(t_ray *r, t_obj *o, t_hit_rec *rec);

/* Colors */
t_color     int_to_color(int c);
int         color_to_int(t_color c);
t_vec3	    color_to_vec3(t_color c);
t_color     lerp_color(t_color a, t_color b, float factor);
t_color     color_x_vec3(t_color col, t_vec3 factor);
t_color     mult_color(t_color a, float factor);
t_color     add_color(t_color a, t_color b);

/* Display */
int	display_default(t_data *rt);
int	display_img(t_data *rt, t_img *img);


/* Ray Generation */
t_obj	*cast_ray_at_pixel(t_data *rt, int x, int y);
t_vec3	ray_at(t_ray *r, float t);
t_vec3	project_a_on_b(t_vec3 a, t_vec3 b);
t_vec3	reflect_ray(t_vec3 dir, t_vec3 normal);

/* Rendering */
bool	hit_anything(t_data *rt, t_ray *r, t_hit_rec *rec);
void	render_scene(t_data *rt);

/* Rendering - Lights */
t_color	pixel_shader(t_data *rt, t_hit_rec *rec, t_color color);
t_color	apply_light_halos(t_data *rt, t_ray *r, t_hit_rec *rec, t_color color);

/* Benchmarking FIXME: to remove for mandatory part */
void	display_fps(t_data *rt, double start_time);


/****************************************/
/*          Utility Functions           */
/****************************************/

void	*ft_xalloc(size_t size);
void	exit_on_err(char *err_message);
void	draw_background(t_img *img, int color);
void	fill_pixel(t_img *img, int x, int y, t_color color);
double	lerp(double start, double end, double curr);
float	deg_to_rad(float deg);
void	print_usage(void);

/****************************************/
/*         Cleaning Functions           */
/****************************************/

int		rt_clean_exit(t_data *rt);
void	rt_cleanup(t_data *rt);


/****************************************/
/*       Matrix & Vector Functions      */
/****************************************/

/* Matrix functions */
void	mat_id(t_mat4 *m);
t_mat4	mat_scale(t_vec4 scale);
t_mat4	mat_rot(float x, char axis);
t_mat4	mat_trans(t_vec4 trans);
t_mat4	mat_mult_mat(t_mat4 m1, t_mat4 m2);
t_vec4	mat_mult_vec4(t_vec4 v, t_mat4 m);
t_vec3	mat_mult_vec3(t_vec3 v, t_mat4 m); // Added by Ismael

/* Inverse matrix functions */
t_mat4	mat_inv(t_mat4 a, double f);
double	determinant(t_mat4 a, double k);
t_mat4	transpose(t_mat4 a, t_mat4 fac, double r);

/* Matrix Utilities */
t_mat4	orient_to_rot(t_vec3 direct);
t_mat4	mat_rot_compound(float x, float y, float z);

/* Vectors by copy */
t_vec3  point(float x, float y, float z);		// FIXME: might remove, sets w to 1
t_vec3	vec3(float x, float y, float z);
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

/* Vector Utilities */
t_vec4	vec3_to_vec4(t_vec3 input, char type);
t_vec3	vec4_to_vec3(t_vec4 input);
void	print_vec3(t_vec3 v);       /* Debug utils. FIXME: to remove at end of project */


/****************************************/
/*          Camera Functions            */
/****************************************/

void	cam_calc_transforms(t_data *rt);


t_vec4	vec4(float x, float y, float z, float w);
t_mat4	mat4(t_vec4 a, t_vec4 b, t_vec4 c, t_vec4 d);
void	cam_init(t_data *rt);
void	cam_calc_view(t_data *rt);
void	cam_calc_project(t_data *rt);
void	cam_generate_rays(t_data *rt);
void	cam_recalc(t_data *rt);


/****************************************/
/*    Parsing & Scene Initialization    */
/****************************************/

/* Parsing Functions */
void	init_parse(t_parse *dat);
int		open_scene(t_parse *dat, char *path);
int		check_tok(char *input, char** tok);
int		check_scene(t_parse *dat);
void	parse_free(t_parse *dat);
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
void	init_parse_fct_ptrs(t_data *rt);
void	count_objects(t_data *rt);
void	init_color(t_color *clr, char *input);
void	init_float_triplet(t_vec3 *vec, char *input);
void	init_ambient(t_data *rt, char **input, int obj_nb);
void	init_camera(t_data *rt, char **input, int obj_nb);
void	init_light(t_data *rt, char **input, int obj_nb);
void	init_plane(t_data *rt, char **input, int obj_nb);
void	init_sphere(t_data *rt, char **input, int obj_nb);
void	init_cylinder(t_data *rt, char **input, int obj_nb);



/****************************************/
/*                BONUS               */
/****************************************/

/* Shape Specific UV mapping */
t_vec2 spherical_map(t_vec3 p);
t_vec2 planar_map(t_vec3 p);
t_vec2 cylindrical_map(t_vec3 p);

/* Checkerboard Pattern */
t_texture uv_checkers(int width, int height, t_color c1, t_color c2);
t_color uv_pattern_at_checkers(t_texture texture, t_vec2 uv);

// /* Image texture mapping */
t_color uv_pattern_at_image(t_texture texture, float u, float v);
t_color	obj_get_color(t_data *rt, t_vec3 p, t_obj *obj);

// /* Normal Mapping */
t_vec2	uv_at(t_vec3 p, t_obj *obj);
t_vec3	get_normal_map(t_vec3 p, t_obj *obj);
t_vec3	obj_get_normal(t_vec3 normal, t_vec3 p, t_obj *obj);



/* Reading PPM Files */
void 	parse_ppm_skip_comment(char *buf, int *p);
void	parse_ppm_skip_whitespace(char *buf, int *p);
int 	parse_ppm_identifier(char *buf, int *p);
void 	parse_ppm_width(t_ppm *img, char *buf, int *p);
void 	parse_ppm_height(t_ppm *img, char *buf, int *p);
void 	parse_ppm_maxval(t_ppm *img, char *buf, int *p);
void 	parse_ppm_header(t_ppm *img, char *buf, int *p);
void	parse_ppm(t_ppm *img, char *buf);
void	read_ppm(t_ppm *img, char *path);



/****************************************/
/*           Debug Utilities            */
/****************************************/

void	print_scene_after_init(t_data *rt);
void	print_cam_data(t_data *rt);
void	print_obj_data(t_obj *obj);
void	print_data_to_screen(t_data *rt);
void	print_obj_info(t_data *rt, int id);

#endif // MINIRT_H