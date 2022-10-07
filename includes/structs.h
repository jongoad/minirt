#ifndef STRUCTS_H_
# define STRUCTS_H_

#include "defines_enums.h"

/*******************************/
/*      Structs Prototypes     */
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

typedef struct s_quadratic
{
    float	a;
    float	half_b;
    float	c;
    float	discriminant;
	float	sqrtd;
	float	root;
}	t_quadratic;

typedef	struct s_color
{
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;
	float		weight;
}	t_color;

/*******************************/
/*        3D Data Structs      */
/*******************************/

/* 4x4 Matrix */
typedef struct s_mat4
{
	double	m[4][4];
}	t_mat4;

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
}	t_ambient;

/* Camera object */
typedef struct s_camera
{
	
	/* Currently used */
	t_vec4		pos4;				/* Position of camera */
	t_vec3		pos;
	t_vec3		aim;				/* Direction camera is pointing */

	t_mat4		p;					/* Matrix for object position and orientation */ 
	int			fov;				/* Field of view in degrees */

	t_mat4		w_to_c;		/* World to camera transform */ 
	t_mat4		c_to_w;		/* Camera to world transform (inverse of world_to_camera); */


	/* T0 be checked */
	t_vec3		horizontal;			/* view_w vector  */
	t_vec3		vertical;			/* view_h vector  */
	t_vec3		low_left;			/* Vector from origin to lower left corner */
	int			img_w;				/* Width of image in pixels */
	int			img_h;				/* Height of image in pixels */
	float		view_w;				/* Width of the viewport */
	float		view_h;				/* Height of the viewport */
	float		z_offset;			/* Distance of focal point from image plane, this will change the FOV */

}	t_camera;

/* Generic scene object */
typedef struct s_obj
{
	/* Object reference data*/
	t_vec3		center;
	t_vec3		normal; 		/* for cylinders, planes */
	t_vec3		color;			/* object initial color vec3 */
	t_color		clr;			/* Colour data for object */
	float		ratio;			/* Brightness ratio for light objects */
	float		width;			/* for cylinders */
	float		radius;			/* for spheres */
	float		height;			/* for cylinders */
	t_mat4		p;				/* Matrix for object position and orientation */ 
	
	/* Object current data */
	t_vec3		c_center;
	t_vec3		c_orient;
	float		c_width;
	float		c_radius;
	float		c_height;

	/* Transformation data */
	float		scale;
	t_vec3		rot;
	t_vec3		trans;

	// FIXME: TEMP obj attributes for cylinders
	// TODO: remove once we have the inverse matrices set up
	float		cyl_offset;

	/* Function pointers for ray collision per object */
	bool		(*hit)(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);	/* Function ptr for any object type */
	char		type;
}	t_obj;

/* Point light object */
typedef struct s_light_pt
{
	t_vec3	center;
	t_vec3	color;
	t_obj	plane;
}	t_light_pt;

/******************************************/
/*        Raytracing Utility Structs      */
/******************************************/

typedef struct s_hit_rec
{
	t_vec3	p;				/* Coords of point of collision */
    t_vec3	normal;			/* Unit vector representing the normal to the surface at collision */
    t_vec3	color;			/* Color vector at collision */
    double	t;				/* Distance to point of collision */
    int		obj_id;			/* ID of the object with which collision happened */
    bool	antialias;		/* If thew point is near an edge, use antialiasing */
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
	t_ambient	ambient;		/* Ambient light data */
	t_parse		parse;			/* Parse data */
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
	int			nb_objs;
	int			selected_obj_id;	/* For dynamic resizing/translation */
	int			win_h;
	int			win_w;
	int			background;
}	t_data;

#endif	//STRUCTS_H_