#ifndef STRUCTS_H_
# define STRUCTS_H_

/* User Includes */
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
typedef struct s_camera		t_camera;
typedef struct s_parse		t_parse;
typedef struct s_img		t_img;
typedef struct s_data		t_data;
typedef struct s_toggle		t_toggle;
typedef struct s_ppm		t_ppm;
typedef struct s_texture	t_texture;

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
	//Check if all 6 of these iterators are needed
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
	unsigned char 	b;
}	t_color;

/* 4x4 matrix */
typedef struct s_mat4
{
	double	m[4][4];
}	t_mat4;


/*******************************/
/*            BONUS            */
/*******************************/

/* PPM image data */
typedef struct s_ppm
{
	int				type;		/* .PPM file type (P6 or P3)*/
	int				width;
	int				height;
	unsigned int	maxval;		/* Maximum colour value */
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
	t_color c2;
}	t_texture;

/*******************************/
/*        3D Data Structs      */
/*******************************/

/* UV float data*/
//FIXME - Check if this is necessary
typedef struct s_vec2
{
	float u;
	float v;
}	t_vec2;

/* Vector/vertex with 3 components */
//FIXME - Should remove w value from this
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

/* UV coordinate struct */
typedef struct s_uv
{
	unsigned int u;
	unsigned int v;
}	t_uv;

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
	/* General camera data */
	t_vec3		pos;					/* Camera origin position */
	int			fov;					/* Field of view in degrees */
	t_vec3		prev_mouse;
	bool		is_move;

	/* Image plane size data */
	float		view_w;
	float		view_h;

	/* Camera rotation data */
	t_mat4		m_pitch;				/* Pitch rotation matrix */
	t_mat4		m_yaw;					/* Yaw rotation matrix */
	float		pitch;					/* Current pitch value (rotation in degrees) */
	float		yaw;					/* Current yaw value (rotation in degrees) */
	
	/* Camera direction vectors */
	t_vec3		forward;
	t_vec3		up;						/* Default up vector (0, 1, 0) */
	t_vec3		right;
	t_vec3		real_up;				/* To calculate relative transforms */

	/* Camera rays */
	t_vec3		rays[IMG_H][IMG_W];		/* Pre-cached vector array */
}	t_camera;

/* Generic scene object */
typedef struct s_obj
{
	/* General object data */
	char		type;					/* Object type specifier */
	t_vec3		pos;					/* Position of object origin */
	t_color		clr;					/* Colour data for object */
	float		ratio;					/* Brightness ratio for light objects */
	float		radius;					/* For spheres */
	float		width;					/* For cylinders */
	float		half_height;			/* For cylinders */

	/* Object orientation vectors  */
	t_vec3		fwd;
	t_vec3		up;
	t_vec3		right;

	/* Coordinate transformation matrices*/
	//Check if these are being used
	t_mat4		l_to_w;					/* Local to world transforms matrix */
	t_mat4		w_to_l;					/* World to local transforms matrix */

	/* Object material data */
	t_texture	texture;				/* Texture file */
	t_texture	normal;					/* Normal map file */
	float		shininess;				/* Reflectivity value */
	t_color		diffuse_clr;			/* This should be set to default object colour */
	t_color		specular_clr;

	/* Function pointers for ray collision per object */
	bool		(*hit)(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);	/* Function ptr for any object type */
	

	/* Transformation data */
	//This data might not be necesssary
	float		scale;
	t_vec3		rot;
	t_vec3		trans;
}	t_obj;

/******************************************/
/*        Raytracing Utility Structs      */
/******************************************/
/* Ray/object intersection data */
typedef struct s_hit_rec
{
	t_vec3	p;						/* Coords of point of collision */
    t_vec3	normal;					/* Unit vector representing the normal to the surface at collision */
    t_color	color;					/* Color vector at collision */
    double	t;						/* Distance to point of collision */
    int		obj_id;					/* ID of the object with which collision happened */
    bool	inside_surface;			/* If thew point is near an edge, use antialiasing */
    bool	hit_anything;			/* FIXME: not sure if will be needed, but useful for debugging */
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

/* Toggle settings */
typedef struct s_toggle
{
	bool	is_normal;
	bool	is_texture;
	bool	is_point_light;
	bool	is_light_halo;
	bool	is_specular;
	bool	is_left_click;				/* Track if the left mouse button is pressed down */
	bool	is_display_debug;			/* Toggle showing debug information on screen */
}	t_toggle;
 
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
	t_obj		**lights;
	int			nb_lights;
	t_vec3		ambt_light;
	t_color		background;
	int			nb_objs;
	int			selected_obj_id;		/* For dynamic resizing/translation */
	int			win_h;
	int			win_w;
	t_toggle	toggle;					/* Struct for all toggleable variables */
	//Should move mlx, window data to its own struct for clarity
}	t_data;

#endif	//STRUCTS_H_