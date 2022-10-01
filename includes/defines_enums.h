#ifndef DEFINES_ENUMS_H_
# define DEFINES_ENUMS_H_

/****************************/
/*         Defines          */
/****************************/

/* Image Controls */
# define ASPECT_RATIO ((float)16 / (float)9)
# define IMG_W 1200
# define IMG_H (int)(IMG_W / ASPECT_RATIO)



/* Math Defines */
# define T_INF	1e10
# define T_MIN	0.01F


/* Flag Defines */
# define NO_HIT -1


/****************************/
/*          Enums           */
/****************************/

/* Colour Codes */
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

/* Scene Object Types*/
typedef enum e_obj_types
{
	T_SPH	= 's',
	T_CYL	= 'c',
	T_PLANE	= 'p',
	T_CONE	= 'o'
}	e_obj_types;

#endif	//DEFINES_ENUMS_H_