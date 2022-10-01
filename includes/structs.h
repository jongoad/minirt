#ifndef STRUCTS_H_
# define STRUCTS_H_

/*******************************/
/*       Utility Structs       */
/*******************************/

/* Iterator */
typedef struct s_i
{
	int x;
	int y;
	int z;
}	t_i;

/* Vector and Point Data */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef t_vec3	t_point;
typedef t_vec3	t_color;

/* Vector with four components */
typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;

}	t_vec4;

typedef struct s_quadratic
{
    float	a;
    float	half_b;
    float	c;
    float	discriminant;
	float	sqrtd;
	float	root;
}	t_quadratic;

typedef	struct s_ray_vec3
{
	t_vec3 	orig;			/* Originating point of ray (camera focal point) */
	t_vec3	dir;			/* Secondary point of ray (pixel on image plane) */
}	t_ray_vec3;

/* Camera data */
typedef struct s_camera
{
	t_vec3		pos;				/* Position of camera */
	t_vec3		aim;				/* Direction camera is pointing */
	t_vec3		horizontal;			/* view_w vector  */
	t_vec3		vertical;			/* view_h vector  */
	t_vec3		low_left;			/* Vector from origin to lower left corner */
	float		**world_to_cam;		/* World to camera coords transform */
	float		**cam_to_world;		/* Camera to world coords transform */
	int			img_w;				/* Width of image in pixels */
	int			img_h;				/* Height of image in pixels */
	float		view_w;				/* Width of the viewport */
	float		view_h;				/* Height of the viewport */
	float		z_offset;			/* Distance of focal point from image plane, this will change the FOV */

}	t_camera;


typedef struct s_hit_rec	t_hit_rec;
typedef struct s_obj		t_obj;
typedef struct s_obj
{
	/* Object reference data*/
	t_vec3		center;
	t_vec3		orientation; 	/* for cylinders, planes */
	t_vec3		color;			/* object initial color vec3 */
	float		width;			/* for cylinders */
	float		radius;			/* for spheres */
	float		height;			/* for cylinders */

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

	/* Function pointers for ray collision per object */
	bool		(*hit)(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec);	/* Function ptr for any object type */
	bool		(*hit_no_rec)(t_ray_vec3 *r, t_obj *o);	/* Function ptr for any object type */
	char		type;



}	t_obj;

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

typedef struct s_light_pt
{
	t_vec3	pos;
	t_vec3	color;
}	t_light_pt;

/* Master data */
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*win_name;
	t_img		*img;
	t_camera	cam;
	t_obj		**objs;
	t_light_pt	*lights;
	int			nb_lights;
	t_vec3		ambt_light;
	int			nb_objs;
	int			selected_obj_id;	/* For dynamic resizing/translation */
	int			win_h;
	int			win_w;
	int			background;
}	t_data;

#endif	//STRUCTS_H_