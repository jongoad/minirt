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
typedef	struct s_ray		t_ray;
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
	float u;
	float v;
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
typedef	struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char 	b;
}	t_color;

/***** General Utility *****/

/* Iterator */
typedef struct s_i
{
	int	x;
	int y;
	int z;
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
	double	dir_dot_fwd;			/* For cones and cylinders */
	double	oc_dot_fwd;				/* For cones and cylinders */
	t_vec3	oc;
}	t_quadratic;

/***** Texture Mapping *****/

/* PPM image data */
typedef struct s_ppm
{
	int				type;			/* .PPM file type (P6 or P3) */
	int				width;
	int				height;
	unsigned int	maxval;			/* Maximum colour value */
	t_color			**pixels;		/* Array of pixel colour data */
}	t_ppm;

/* Texture data */
typedef struct s_texture
{
	int		width;
	int		height;
	t_ppm	image;					/* Loaded image data */
	bool	is_image;
	bool	is_checkers;
	t_color	c1;						/* Colour 1 for checkers pattern */
	t_color c2;						/* Colour 2 for checkers pattern */
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
	float		angle;					/* Initial angle submitted by user */
	float		angle_ofs;				/* For cones, represents 1 + half_tan(angle)^2 */
	float		ref_radius;
	float		ref_half_height;

	/* Object orientation vectors  */
	t_vec3		fwd;
	t_vec3		up;
	t_vec3		right;

	/* Object material data */
	t_texture	texture;				/* Texture file */
	t_texture	normal;					/* Normal map file */
	float		shininess;				/* Reflectivity value */

	/* Function pointers for ray collision per object */
	bool		(*hit)(t_ray *r, t_obj *o, t_hit_rec *rec);
	
	/* Transformation data */
	float		scale;
	t_vec3		rot;
}	t_obj;

/***** Raytracing data *****/

/* Ray vector */
typedef	struct s_ray
{
	t_vec3 	orig;					/* Originating point of ray (camera focal point) */
	t_vec3	dir;					/* Secondary point of ray (pixel on image plane) */
}	t_ray;

/* Ray/object intersection data */
typedef struct s_hit_rec
{
	t_vec3	p;						/* Coords of point of collision */
    t_vec3	normal;					/* Unit vector representing the normal to the surface at collision */
    t_color	color;					/* Color vector at collision */
    double	t;						/* Distance to point of collision */
    t_obj	*obj;					/* Ptr to the object with which collision happened, NULL if no collision */
    bool	inside_surface;			/* If thew point is near an edge, use antialiasing */
    bool	hit_anything;			/* FIXME: not sure if will be needed, but useful for debugging */
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
	t_obj		*selected;		   		/* Ptr to the object user selected with the mouse */
	int			win_h;
	int			win_w;
	t_toggle	toggle;					/* Struct for all toggleable variables */
}	t_data;

#endif	//STRUCTS_H_