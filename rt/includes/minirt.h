#ifndef MINIRT_H
# define MINIRT_H

/* System Includes */
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* User Includes */
#include "../libft/libft.h"
#include "error.h"
#include "enums.h"
#include "structs.h"

/* Defines */
# define IMG_W 1000
# define IMG_H 562

/* PARSE STUFF */

#define READ_SIZE 100000
#define NB_OBJ_TYPE 6
#define BONUS 1



typedef struct s_parse
{
	int fd;
	char *buf;
	char **split;
	char ***scene;
	char **tok;
	int	(*f[NB_OBJ_TYPE])(char **obj);
}	t_parse;


/* Matrix functions */
float	**mat_id(int fill, int fill_diagonal);
float	**mat_rot(float x, char axis);
float	**mat_scale(t_point scale);
float	**mat_trans(t_point translate);
float	**mat_mult_mat(float **m1, float **m2);
void	mat_mult_vec4(t_point *v, float **mat);
void	mat_free(float **mat);




/* Parsing Functions */
void	init_parse(t_parse *dat);
int		open_scene(t_parse *dat, char *path);
int		check_tok(char *input, char** tok);
int		check_scene(t_parse *dat);
int		parse(t_data *rt, char *path);

/* Individual Object Parsing Functions */
int		parse_ambient(char **obj);
int		parse_camera(char **obj);
int		parse_light(char **obj);
int		parse_plane(char **obj);
int		parse_sphere(char **obj);
int		parse_cylinder(char **obj);

/* Parsing Utils */
int 	check_rgb(char *rgb);
int		check_float(char *val, float lim1, float lim2);
int		check_int(char *val, int lim1, int lim2);
int		check_orientation(char *orient);
int		check_coords(char *coord);
void	replace_whitespace(t_parse *dat);


void	*ft_xalloc(size_t size);












#endif 