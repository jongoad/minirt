#ifndef STRUCTS_H_
# define STRUCTS_H_

#include "defines_enums.h"

/*******************************/
/*      Struct Prototypes     */
/*******************************/
typedef struct s_hit_rec	t_hit_rec;
typedef struct s_obj		t_obj;
typedef struct s_i			t_i;
typedef struct s_quadratic	t_quadratic;
typedef	struct s_color		t_color;
typedef struct s_vec3		t_vec3;
typedef struct s_vec4		t_vec4;
typedef	struct s_ray_vec3	t_ray_vec3;
typedef struct s_ambient	t_ambient;
typedef struct s_light_pt	t_light_pt;
typedef struct s_camera		t_camera;
typedef struct s_parse		t_parse;
typedef struct s_img		t_img;
typedef struct s_data		t_data;

/*******************************/
/*         QoL Typedefs        */
/*******************************/
typedef t_vec3	t_point;


/*******************************/
/*       Utility Structs       */
/*******************************/

/* Iterator */
typedef struct s_i
{
	int x;
	int y;
	int z;

	int i;
	int j;
	int k;
}	t_i;

/* Quadratic solver */
typedef struct s_quadratic
{
    float	a;
    float	half_b;
    float	c;
    float	discriminant;
	float	sqrtd;
	float	root;
}	t_quadratic;

/* Color data */
typedef	struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

/* 4x4 matrix */
typedef struct s_mat4
{
	double	m[4][4];
}	t_mat4;


/*******************************/
/*        3D Data Structs      */
/*******************************/

/* Vector/vertex with 3 components */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec3;

/* Vector/vertex with four components */
typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;

}	t_vec4;

/* Ray vector */
typedef	struct s_ray_vec3
{
	t_vec3 	orig;					/* Originating point of ray (camera focal point) */
	t_vec3	dir;					/* Secondary point of ray (pixel on image plane) */
}	t_ray_vec3;


/*******************************/
/*        Objects Structs      */
/*******************************/

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
	int			fov;					/* Field of view in degrees */

	t_mat4		m_pitch;
	t_mat4		m_yaw;
	float		pitch;
	float		yaw;
	t_vec3		prev_mouse;

	/* Camera direction vectors */
	t_vec3		forward;
	t_vec3		up;						/* Default up vector (0, 1, 0) */
	t_vec3		right;
	t_vec3		real_up;				/* To calculate relative transforms */
	t_vec3		rays[IMG_H][IMG_W];		/* Pre-cached vector array */
	bool		is_move;


	float		view_w;
	float		view_h;

}	t_camera;

/* Generic scene object */
typedef struct s_obj
{
	/* Object reference data*/
	t_vec3		pos;
	t_vec3		fwd; 			/* for cylinders, planes */
	t_color		clr;			/* Colour data for object */
	float		ratio;			/* Brightness ratio for light objects */
	float		width;			/* for cylinders */
	float		radius;			/* for spheres */
	float		half_height;			/* for cylinders */
	
	/* Object current data */
	t_vec3		pos_ref; //c_center
	t_vec3		fwd_ref;
	float		width_ref;
	float		radius_ref;
	float		height_ref;

	/* Transformation data */
	float		scale;
	t_vec3		rot;
	t_vec3		trans;

	/* Object transformation */
	t_vec3		up;
	t_vec3		right;
	t_mat4		l_to_w;		/* Local to world transforms matrix */
	t_mat4		w_to_l;		/* World to local transforms matrix */

	/* Function pointers for ray collision per object */
	bool		(*hit)(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);	/* Function ptr for any object type */
	char		type;
}	t_obj;

/* Point light object */
typedef struct s_light_pt
{
	t_vec3	pos;
	t_vec3	color;
	t_obj	plane;
}	t_light_pt;

/******************************************/
/*        Raytracing Utility Structs      */
/******************************************/
/* Ray/object intersection data */
typedef struct s_hit_rec
{
	t_vec3	p;				/* Coords of point of collision */
    t_vec3	normal;			/* Unit vector representing the normal to the surface at collision */
    t_color	color;			/* Color vector at collision */
    double	t;				/* Distance to point of collision */
    int		obj_id;			/* ID of the object with which collision happened */
    bool	inside_surface;		/* If thew point is near an edge, use antialiasing */
    bool	hit_anything;	/* FIXME: not sure if will be needed, but useful for debugging */
}	t_hit_rec;


/*******************************/
/*       Parse Data Struct     */
/*******************************/
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

 

/* Master data */
typedef struct s_data
{
	t_ambient	ambient;				/* Ambient light data */
	t_parse		parse;					/* Parse data */
	void		*mlx_ptr;
	void		*win_ptr;
	char		*win_name;
	t_img		*img;
	t_camera	cam;
	t_obj		**objs;
	t_light_pt	*lights_struct;
	t_obj		**lights;
	int			nb_lights;
	t_vec3		ambt_light;
	t_color		background;
	int			nb_objs;
	int			selected_obj_id;		/* For dynamic resizing/translation */
	bool		apply_light_halos;		/* To activate/deactivate with a key hook */
	bool		left_clicking;		/* To activate/deactivate with a key hook */
	int			win_h;
	int			win_w;
}	t_data;

#endif	//STRUCTS_H_