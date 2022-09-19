#include "minirt.h"

/* Split individual scene lines by space */
void	split_scene(t_parse *dat)
{
	int i;

	i = 0;
	while(dat->split[i])
	{
		dat->scene[i] = ft_split(dat->split[i], ' ');
		i++;
	}
}

/* Setup parse variables */
void init_parse(t_parse *dat)
{
	dat->f[0] = parse_ambient();
	dat->f[1] = parse_camera();
	dat->f[2] = parse_light();
	dat->f[3] = parse_plane();
	dat->f[4] = parse_sphere();
	dat->f[5] = parse_cylinder();
}

/* Attempt to open and read scene file */
int	open_scene(t_parse *dat, char *path)
{
	int status;
	int i;

	status = 0;
	i = 0;
	dat->fd = open(path, O_RDONLY);
	if (dat->fd == -1)
		return (0);
	dat->buf = ft_xalloc(READ_SIZE + 1);
	status = read(dat->fd, dat->buf, READ_SIZE);
	if (status == -1)
		return (0);
	dat->split = ft_split(dat->buf, '\n');
	while (dat->split && dat->split[i])
		i++;
	if (i == 0)
		return (0);
	//Replace any whitespace with spaces
	split_scene(dat);
	return (1);
}

/* Attempt to match token for object type */
int	check_tok(t_parse *dat, char** tok)
{
	t_i i;

	i.y = 0;
	i.x = 0;
	while (dat->scene[i.y])
	{
		i.x = 0;
		while (tok[i.x])
		{
			if (!ft_strcmp(dat->scene[i.y][0], tok[i.x]))
				return (i.x);
			i.x++;
		}
		i.y++;
	}
	return (-1);
}

/* Check each scene element for validity */
int check_scene(t_parse *dat)
{
	t_i i;
	int res;
	char **tok = {"A", "C", "L", "pl", "sp", "cy"};

	i.x = 0;
	//Check first field of each line to match token
	while (dat->scene[i.x])
	{
		res = check_tok(dat, tok);
		if (res == -1)
			return (0);
		if (!dat->f[res](dat->scene[i.x]))
			return (0);
		i.x++;
	}
	return (1);
}

/* Create objects based on parse data */
void	init_scene(t_data *rt, t_parse *dat)
{
	//Count number of objects

	//Allocate space for objects

	//Populate data
}

/* Check if scene if valid */
void	parse(t_data *rt, char *path)
{
	t_parse dat;

	init_parse(&dat);
	if (!open_scene(&dat, path))
		exit_error_clean();
	else if (!check_scene(&dat))
		exit_error_clean();
	init_scene(rt, &dat);
}








/* 
1. Read scene one line at a time
2. Split each line
3. Validate each line
4. Init scene
*/



/*
A 0.2 255,255,255								Ambient light

C -50,0,20 0,0,0 70								Camera
L -40,0,30 0.7 255,255,255						Light

pl 0,0,0 0,1.0,0 255,0,225						Plane
sp 0,0,20 20 255,0,0							sp
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255	cy
*/