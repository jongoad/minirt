#ifndef MINIRT_H
# define MINIRT_H

/* System Includes */
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* User Includes */
// # include "../minilibx_opengl/mlx_opengl.h"
# include <mlx.h>
# include "../libft/libft.h"


# include "rt_one_weekend.h"


/* Defines */
# define ASPECT_RATIO ((float)16 / (float)9)
# define IMG_W 1200
# define IMG_H (int)(IMG_W / ASPECT_RATIO)

# define INF	1e10
# define T_MIN	0.5F

/* Colors */
typedef enum e_colors
{
	BLACK	= 0x000000,
	BLUE	= 0x0000FF,
	CYAN	= 0x00FFFF,
	GREY	= 0x222222,
	ORANGE	= 0xFF7700,
	PINK	= 0xFF00FF,
	RED		= 0xFF0000,
	WHITE	= 0xFFFFFF,
	YELLOW	= 0xFFFF00
}	t_colors;

typedef enum e_obj_types
{
	T_SPH	= 's',
	T_CYL	= 'c',
	T_PLANE	= 's',
	T_CONE	= 's'
}	e_obj_types;
/* Structs */


/* Iterator */
typedef struct s_i
{
	int x;
	int y;
	int z;
}	t_i;

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
	t_point		pos;
	t_color		clr;

}	t_object;

typedef struct s_hit_rec	t_hit_rec;
typedef struct s_obj		t_obj;
typedef struct s_obj
{
	t_vec3		center;
	t_vec3		orientation; 	/* for cylinders */
	t_vec3		color;			/* object initial color */
	float		width;			/* for cylinders */
	float		radius;			/* for spheres */
	float		height;			/* for cylinders */
	bool		(*hit)(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec, float t_min);	/* Function ptr for any object type */
	char		type;
}	t_obj;

typedef struct s_hit_rec
{
	t_vec3	p;			/* Coords of point of collision */
    t_vec3	normal;		/* Unit vector representing the normal to the surface at collision */
    double	t;			/* Distance to point of collision */
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
	t_object	**objects;	// Do we want to add objects dynamically ?
	// t_object	*objects;	
	int			nb_objs;
	t_mlx		mlx;
	int			win_h;
	int			win_w;
}	t_data;

/* Initialization */
void	rt_init(t_data *rt, char *filepath);

/* Hooks */
void	set_hooks(t_data *rt);

/* Colors */
int		int_to_color(int r, int g, int b);
void    color(t_color *c);
int     vec3_to_color(t_vec3 *c);
int     vec3_to_color_copy(t_vec3 c);

/* Display */
int	display_default(t_data *rt);
int	display_img(t_data *rt, t_img *img);


/* Ray Generation */
t_ray		*generate_primary_ray(t_data *data, int x, int y);
t_point		*init_pixel_point(t_data *data, int x, int y);

t_data		*get_data(void);
t_vector	*get_vector(t_point *origin, t_point *second);

/* Matrix functions */
float	**matrix_identity(int fill, int fill_diagonal);
float	**matrix_rotation(float x, char axis);
float	**matrix_scale(t_point scale);
float	**matrix_translate(t_point translate);
float	**matrix_mult_mat(float **m1, float **m2);
void	matrix_mult_point(t_point *v, float **mat);
void	matrix_free(float **mat);

/* Utils */
void	*ft_xalloc(size_t size);
void	exit_on_err(char *err_message);
void	draw_background(t_img *img, int color);
void	fill_pixel(t_img *img, int x, int y, int color);
double	lerp(double start, double end, double curr);

/* Cleanup */
int		rt_clean_exit(t_data *rt);
void	rt_cleanup(t_data *rt);




/* Vectors by copy */

double	invsqrt(double y);

t_vec3	vec3(double x, double y, double z);
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

/* Vectors by new malloced pointer */
t_vec3 *add_vec3_new(t_vec3 *a, t_vec3 *b);
t_vec3 *add3_vec3_new(t_vec3 *a, t_vec3 *b, t_vec3 *c);
t_vec3 *sub_vec3_new(t_vec3 *a, t_vec3 *b);
t_vec3 *mult_vec3_vec3_new(t_vec3 *a, t_vec3 *b);
t_vec3 *mult_vec3_new(t_vec3 *v, double b);
t_vec3 *div_vec3_new(t_vec3 *v, double b);
t_vec3 *unit_vec3_new(t_vec3 *v);
t_vec3 *cross_vec3_new(t_vec3 *a, t_vec3 *b);
t_vec3 *negate_vec3_new(t_vec3 *v);

#endif // MINIRT_H