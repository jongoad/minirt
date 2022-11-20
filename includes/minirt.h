/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:01 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 17:08:04 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"

/* Local File Includes */
# include "normfail.h"
# include "structs.h"
# include "defines_enums.h"
# include "error.h"

/*******************************/
/*    Function Declarations    */
/*******************************/

/* Hooks */
void	set_hooks(t_data *rt);

/* Object intersection functions */
int		hit_sphere(t_ray *r, t_obj *o, t_hit_rec *rec);
int		hit_sphere_no_hit_rec(t_ray *r, t_obj *o);
int		hit_plane(t_ray *r, t_obj *o, t_hit_rec *rec);
int		hit_disk(t_ray *r, t_obj *o, t_hit_rec *rec);
int		hit_caps(t_ray *r, t_obj *o, t_hit_rec *rec);
int		hit_cylinder(t_ray *r, t_obj *o, t_hit_rec *rec);
int		hit_cone(t_ray *r, t_obj *o, t_hit_rec *rec);

/* Colors */
t_color	int_to_color(int c);
int		color_to_int(t_color c);
t_vec3	color_to_vec3(t_color c);
t_color	lerp_color(t_color a, t_color b, float factor);
t_color	color_x_vec3(t_color col, t_vec3 factor);
t_color	mult_color(t_color a, float factor);
t_color	add_color(t_color a, t_color b);

/* Display */
int		display_default(t_data *rt);

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
bool	hit_lights(t_data *rt, t_ray *r, t_hit_rec *rec);

/* Benchmarking FIXME: to remove for mandatory part */
void	display_fps(t_data *rt, double start_time);

/****************************************/
/*          Utility Functions           */
/****************************************/

void	fill_pixel(t_img *img, int x, int y, t_color color);
float	deg_to_rad(float deg);
void	print_usage(void);
float	roundf_precision(float n, float p);
int		count_array_2d(char **array);

/****************************************/
/*        Memory & Error Functions      */
/****************************************/

t_data	*get_data(void);
int		rt_clean_exit(t_data *rt);
void	rt_cleanup(t_data *rt);
void	exit_on_err(char *err_message);
int		return_on_err(char *err_msg, int retval);
void	*ft_xalloc(size_t size);

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

/* Matrix Utilities */
t_mat4	mat_rot_compound(float x, float y, float z);

/* Vectors by copy */
t_vec3	vec3(float x, float y, float z);
t_vec3	add_vec3(t_vec3 a, t_vec3 b);
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
void	print_vec3(t_vec3 v);

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
/*           Parsing Functions          */
/****************************************/

/* Main Parsing */
void	init_parse(t_parse *dat);
int		open_scene(t_parse *dat, char *path);
int		check_tok(char *input, char **tok);
int		check_scene(t_parse *dat);
int		parse(t_data *rt, char *path);

/* Individual Object Parsing */
int		parse_ambient(char **obj);
int		parse_camera(char **obj);
int		parse_light(char **obj);
int		parse_plane(char **obj);
int		parse_sphere(char **obj);
int		parse_cylinder(char **obj);
int		parse_cone(char **obj);
int		parse_obj_bonus(char *obj);

/* Parsing Utililities */
int		check_rgb(char *rgb);
int		check_orientation(char *orient);
int		check_coords(char *coord);
int		check_path(char *path, char type);
int		validate_float(char *val);
int		check_float(char *val, float lim1, float lim2);
int		check_int(char *val, int lim1, int lim2);
void	replace_whitespace(t_parse *dat);
int		parse_error(t_parse *dat, char *err, char **line);
void	parse_free(t_parse *dat);
void	split_scene(t_parse *dat);
char	**create_tok(void);
bool	check_orient_zero(char **split);

/****************************************/
/*       Initialization Functions       */
/****************************************/

/* Main Initialization */
void	rt_init(t_data *rt, char *filepath);
void	rt_init_img(t_data *rt);
void	rt_init_mlx(t_data *rt, char *filename);
void	init_toggle(t_data *rt);

/* Scene Initialization */
void	init_cam_angles(t_data *rt);
void	init_scene(t_data *rt);
void	init_scene_allocate(t_data *rt);

/* Object Initialization */
void	init_ambient(t_data *rt, char **input, int obj_nb);
void	init_camera(t_data *rt, char **input, int obj_nb);
void	init_light(t_data *rt, char **input, int obj_nb);
void	init_plane(t_data *rt, char **input, int obj_nb);
void	init_sphere(t_data *rt, char **input, int obj_nb);
void	init_cylinder(t_data *rt, char **input, int obj_nb);
void	init_cone(t_data *rt, char **input, int obj_nb);

/* Bonus Attributes Inialization */
void	init_texture(t_obj *obj, char *input);
void	init_normal(t_obj *obj, char *input);
void	init_obj_bonus(t_obj *obj, char **input);

/* Initialization Utilities*/
void	init_color(t_color *clr, char *input);
void	init_float_triplet(t_vec3 *vec, char *input);
void	count_objects(t_data *rt);
void	init_parse_fct_ptrs(t_data *rt);

/****************************************/
/*                BONUS               */
/****************************************/
/* Shape Specific UV mapping */
t_vec2	spherical_map(t_vec3 p);
t_vec2	planar_map(t_vec3 p);
t_vec2	cylindrical_map(t_vec3 p);

/* Checkerboard Pattern */
t_color	uv_pattern_at_checkers(t_texture texture, t_vec2 uv);

/* Image texture mapping */
t_color	uv_pattern_at_image(t_texture texture, t_vec2 uv);
t_color	obj_get_color(t_data *rt, t_vec3 p, t_obj *obj);

/* Normal Mapping */
t_vec2	uv_at(t_vec3 p, t_obj *obj);
t_vec3	get_normal_map(t_vec3 p, t_obj *obj);
t_vec3	obj_get_normal(t_vec3 normal, t_vec3 p, t_obj *obj);

/* Reading & Parsing .PPM Files */
void	parse_ppm_skip_comment(char *buf, int *p);
void	parse_ppm_skip_whitespace(char *buf, int *p);
int		parse_ppm_identifier(char *buf, int *p);
void	parse_ppm_width(t_ppm *img, char *buf, int *p);
void	parse_ppm_height(t_ppm *img, char *buf, int *p);
void	parse_ppm_maxval(t_ppm *img, char *buf, int *p);
void	parse_ppm_header(t_ppm *img, char *buf, int *p);
int		parse_ppm(t_ppm *img, char *buf);
int		read_ppm(t_ppm *img, char *path);
int		return_on_err_ppm(char *err, int fd, char *buf, char *path);

/****************************************/
/*           Debug Utilities            */
/****************************************/

void	print_scene_after_init(t_data *rt);
void	print_cam_data(t_data *rt);
void	print_obj_data(t_obj *obj);
void	print_data_to_screen(t_data *rt);
void	print_obj_info(t_data *rt, int id);

#endif // MINIRT_H