#ifndef STRUCTS_H_
# define STRUCTS_H_

/* Iterator */
typedef struct s_i
{
	int x;
	int y;
	int z;
}	t_i;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* Colour data */
typedef	struct s_color
{
	int	r;
	int	g;
	int	b;
	int	color; /* (r << 16) | (g << 8) | (b) */
}	t_color;

/* Point data */
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_point;

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
	t_point		pos;
	t_color 	clr;
}	t_vertex;

/* Ray data */
typedef	struct s_ray
{
	t_point 	*origin;			/* Originating point of ray (camera focal point) */
	t_point		*second;			/* Secondary point of ray (pixel on image plane) */
	t_vector	*vec3;				/* Vector created from origin and secondary point */
}	t_ray;
typedef	struct s_ray_vec3
{
	t_vec3 	orig;			/* Originating point of ray (camera focal point) */
	t_vec3	dir;			/* Secondary point of ray (pixel on image plane) */
	// t_vector	*vec3;				/* Vector created from origin and secondary point */
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
	t_point		pos;				/* Position of camera */
	t_vector	aim;				/* Direction camera is pointing */
	float		**world_to_cam;		/* World to camera coords transform */
	float		**cam_to_world;		/* Camera to world coords transform */
	int			img_w;				/* Width of image in pixels */
	int			img_h;				/* Height of image in pixels */
	float		view_w;				/* Width of the camera */
	float		view_h;				/* Height of the camera */
	float		z_offset;			/* Distance of focal point from image plane, this will change the FOV */

}	t_camera;

/* 3D Object */

typedef struct s_mlx
{
}	t_mlx;

typedef struct	s_object
{
	char		type;
	t_point		pos;
	t_color		clr;

}	t_object;

typedef struct s_hit_rec
{
	t_vec3	p;		/* Coords of point of collision */
    t_vec3	normal;	/* Unit vector representing the normal to the surface at collision */
    double	t;		/* Distance to point of collision */
	int		obj_id;	/* ID of the object on which is point of collision */
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

/* Master data */
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*win_name;
	t_img		*img;
	t_camera	cam;
	t_object	**objects;
	int			nb_objs;
	t_mlx		mlx;
	int			win_h;
	int			win_w;
}	t_data;


#endif