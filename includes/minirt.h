#ifndef MINIRT_H
# define MINIRT_H

/* System Includes */
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* User Includes */
#include "../minilibx_opengl/mlx_opengl.h"
#include "../minilibx_opengl/mlx.h"
#include "../libft/libft.h"


/* Defines */
# define IMG_W 1200
# define IMG_H 800


/* Structs */


/* Iterator */
typedef struct s_i
{
	int x;
	int y;
	int z;
}	t_i;

/* Colour data */
typedef	struct s_colour
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_colour;

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
	t_colour 	clr;
}	t_vertex;

/* Ray data */
typedef	struct s_ray
{
	t_point 	*origin;			/* Originating point of ray (camera focal point) */
	t_point		*second;			/* Secondary point of ray (pixel on image plane) */
	t_vector	*vec3;				/* Vector created from origin and secondary point */
}	t_ray;

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
	t_colour	clr;

}	t_object;

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
	t_camera	cam;
	t_object	**objects;
	void		*mlx_ptr;
	void		*win_ptr;
	char		*win_name;
	t_img		*img;
	int			nb_objs;
	t_mlx		mlx;
	int			win_h;
	int			win_w;
}	t_data;

/* Initialization */
void	rt_init(t_data *rt, char *filepath);

/* Hooks */
void	set_hooks(t_data *rt);

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

/* Cleanup */
int		rt_clean_exit(t_data *cont);
void	rt_cleanup(t_data *cont);

#endif // MINIRT_H