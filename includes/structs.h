/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:45:10 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 16:49:48 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* User Includes */
# include "defines_enums.h"

/*******************************/
/*      Struct Prototypes     */
/*******************************/
typedef struct s_hit_rec	t_hit_rec;
typedef struct s_obj		t_obj;
typedef struct s_i			t_i;
typedef struct s_quadratic	t_quadratic;
typedef struct s_color		t_color;
typedef struct s_vec3		t_vec3;
typedef struct s_vec4		t_vec4;
typedef struct s_ray		t_ray;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_parse		t_parse;
typedef struct s_img		t_img;
typedef struct s_data		t_data;
typedef struct s_toggle		t_toggle;
typedef struct s_ppm		t_ppm;
typedef struct s_texture	t_texture;

/*******************************/
/*         Basic Structs       */
/*******************************/

/***** Vectors *****/

/* Vector/vertex with 2 components (used for UV data) */
typedef struct s_vec2
{
	float	u;
	float	v;
}	t_vec2;

/* Vector/vertex with 3 components */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

/* Vector/vertex with four components */
typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

/***** Matrices *****/

/* 4x4 matrix */
typedef struct s_mat4
{
	double	m[4][4];
}	t_mat4;

/***** Colour *****/

/* Color Data */
typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

/***** General Utility *****/

/* Iterator */
typedef struct s_i
{
	int	x;
	int	y;
	int	z;
}	t_i;

/*******************************/
/*       Compound Structs      */
/*******************************/

/***** Math Utility *****/

/* Quadratic solver */
typedef struct s_quadratic
{
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
	float	sqrtd;
	float	root;
	double	dir_dot_fwd;
	double	oc_dot_fwd;
	t_vec3	oc;
}	t_quadratic;

/***** Texture Mapping *****/

/* PPM image data */
typedef struct s_ppm
{
	int				type;
	int				width;
	int				height;
	unsigned int	maxval;
	t_color			**pixels;
}	t_ppm;

/* Texture data */
typedef struct s_texture
{
	int		width;
	int		height;
	t_ppm	image;
	bool	is_image;
	bool	is_checkers;
	t_color	c1;
	t_color	c2;
}	t_texture;

/***** Object Data *****/

/* Ambient light object */
typedef struct s_ambient
{
	t_color	clr;
	float	ratio;
	t_vec3	scene_ambient;
}	t_ambient;

/* Camera object */
typedef struct s_camera
{
	t_vec3		pos;
	int			fov;
	t_vec3		prev_mouse;
	bool		is_move;
	float		view_w;
	float		view_h;
	t_mat4		m_pitch;
	t_mat4		m_yaw;
	float		pitch;
	float		yaw;
	t_vec3		forward;
	t_vec3		up;
	t_vec3		right;
	t_vec3		real_up;
	t_vec3		rays[IMG_H][IMG_W];
}	t_camera;

/* Generic scene object */
typedef struct s_obj
{
	char		type;
	t_vec3		pos;
	t_color		clr;
	float		ratio;
	float		radius;
	float		width;
	float		half_height;
	float		angle;
	float		angle_ofs;
	float		ref_radius;
	float		ref_half_height;
	t_vec3		fwd;
	t_vec3		up;
	t_vec3		right;
	t_texture	texture;
	t_texture	normal;
	float		shininess;
	int			(*hit)(t_ray *r, t_obj *o, t_hit_rec *rec);
	float		scale;
	t_vec3		rot;
}	t_obj;

/***** Raytracing data *****/

/* Ray vector */
typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

/* Ray/object intersection data */
typedef struct s_hit_rec
{
	t_vec3	p;
	t_vec3	normal;
	t_color	color;
	double	t;
	t_obj	*obj;
	bool	inside_surface;
	bool	hit_anything;
}	t_hit_rec;

/* Parsing data */
typedef struct s_parse
{
	bool	has_camera;
	bool	has_ambient;
	int		fd;
	char	*buf;
	char	**split;
	char	***scene;
	char	**tok;
	int		(*f[NB_OBJ_TYPE])(char **obj);
	void	(*f2[NB_OBJ_TYPE])(t_data *rt, char **obj, int obj_nb);
}	t_parse;

/******************************************/
/*      Main Data Structs & MLX Data      */
/******************************************/

/* mlx image */
typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Toggle settings */
typedef struct s_toggle
{
	bool	is_normal;
	bool	is_texture;
	bool	is_light_halo;
	bool	is_specular;
	bool	is_left_click;
	bool	is_display_debug;
}	t_toggle;

/* Master data */
typedef struct s_data
{
	t_ambient	ambient;
	t_parse		parse;
	void		*mlx_ptr;
	void		*win_ptr;
	char		*win_name;
	t_img		*img;
	t_camera	cam;
	t_obj		**objs;
	t_obj		**lights;
	int			nb_lights;
	t_vec3		ambt_light;
	t_color		background;
	int			nb_objs;
	t_obj		*selected;
	int			win_h;
	int			win_w;
	t_toggle	toggle;
}	t_data;

#endif	//STRUCTS_H_