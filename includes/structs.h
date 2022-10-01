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

/* Colour data */
typedef	struct s_color
{
	int	r;
	int	g;
	int	b;
	int	color; /* (r << 16) | (g << 8) | (b) */
	//Color should be an unsigned int??
}	t_color;

/* Point data */
// typedef struct s_point
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	w;
// }	t_point;

/* Vector data */
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
	float	w;

}	t_vector;

/* Vertex data */
typedef	struct s_vertex
{
	// t_point		pos;
	t_color 	clr;
}	t_vertex;

/* Ray data */
typedef	struct s_ray
{
	// t_point 	*origin;			/* Originating point of ray (camera focal point) */
	// t_point		*second;			/* Secondary point of ray (pixel on image plane) */
	t_vector	*vec3;				/* Vector created from origin and secondary point */
}	t_ray;
typedef	struct s_ray_vec3
{
	t_vec3 	orig;			/* Originating point of ray (camera focal point) */
	t_vec3	dir;			/* Secondary point of ray (pixel on image plane) */
	float	t_max;			/* Vector created from origin and secondary point */
}	t_ray_vec3;

typedef	struct s_ray_vec3_ptr
{
	t_vec3 	*orig;			/* Originating point of ray (camera focal point) */
	t_vec3	*dir;			/* Secondary point of ray (pixel on image plane) */
	// t_vector	*vec3;				/* Vector created from origin and secondary point */
}	t_ray_vec3_ptr;

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

/* 3D Object */

typedef struct s_mlx
{
}	t_mlx;

typedef struct	s_object
{
	char		type;
	// t_point		pos;
	t_color		clr;

}	t_object;

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
	t_mlx		mlx;
	int			win_h;
	int			win_w;
	int			background;
}	t_data;

#endif	//STRUCTS_H_