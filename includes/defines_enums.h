#ifndef DEFINES_ENUMS_H_
# define DEFINES_ENUMS_H_

/****************************/
/*         Defines          */
/****************************/

/* Image Controls */
# define ASPECT_RATIO ((float)16 / (float)16)
# define IMG_W 1200
# define IMG_H (int)(IMG_W / ASPECT_RATIO)

/* Parse Defines */
#define READ_SIZE 100000
#define NB_OBJ_TYPE 6
#define BONUS 1

/* Math Defines */
# define T_MAX	1e10
# define T_MIN	0.01F
# define LIGHT_RADIUS	1.05F
# define PI 3.14159265359f

/* Flag Defines */
# define NO_HIT -1

/* Camera Defines */
#define CAM_ROT_RATE 20.0f
#define CAM_TRANS_RATE 0.15f
#define CAM_MAX_TILT 10.0f



/****************************/
/*          Enums           */
/****************************/

/* Colour Codes */
typedef enum e_colors
{
	BLACK	= 0x000000,
	BLUE	= 0x0000FF,
	CYAN	= 0x00FFFF,
	GREEN	= 0x00FF00,
	GREY	= 0x222222,
	ORANGE	= 0xFF7700,
	PINK	= 0xFF00FF,
	RED		= 0xFF0000,
	WHITE	= 0xFFFFFF,
	YELLOW	= 0xFFFF00
}	t_colors;

/* Scene Object Types*/
typedef enum e_obj_types
{
	T_SPH	= 's',
	T_CYL	= 'c',
	T_CONE	= 'o',
	T_PLANE	= 'p',
	T_LIGHT = 'l'
}	e_obj_types;

typedef enum e_vec_types
{
	T_VEC	= 'v',
	T_POINT	= 'p'
}	e_vec_types;

#endif	//DEFINES_ENUMS_H_