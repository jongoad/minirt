#include "minirt.h"

/* Initialize parse variables */
void	init_parse(t_parse *dat)
{
	dat->buf = NULL;															/* Initialize buffer variables to NULL */
	dat->scene = NULL;
	dat->split = NULL;
	dat->f[0] = parse_ambient;													/* Assign object parsing function pointer array */
	dat->f[1] = parse_camera;
	dat->f[2] = parse_light;
	dat->f[3] = parse_plane;
	dat->f[4] = parse_sphere;
	dat->f[5] = parse_cylinder;
	dat->f[6] = parse_cone;
	dat->tok = create_tok();													/* Create token array for accessing function pointer array */
	dat->has_ambient = false;													/* Set duplicate object check variables*/
	dat->has_camera = false;
}

/* Attempt to open and read .rt scene file */
int	open_scene(t_parse *dat, char *path)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	dat->fd = open(path, O_RDONLY);
	if (dat->fd == -1)
		return (parse_error(dat, PARSE_ERR_OPEN, NULL));
	dat->buf = ft_xalloc(READ_SIZE + 1);
	status = read(dat->fd, dat->buf, READ_SIZE);
	if (status == -1)
		return (parse_error(dat, PARSE_ERR_READ, NULL));
	dat->split = ft_split(dat->buf, '\n');										/* Split scene by newline */
	while (dat->split && dat->split[i])											/* Count number of non-empty lines to ensure file contains data */
		i++;
	if (i == 0)
		return (parse_error(dat, PARSE_ERR_EMPTY, NULL));
	replace_whitespace(dat);													/* Trim unecessary whitespace from lines */
	split_scene(dat);															/* Split each scene line into components */
	return (1);
}

/* Attempt to match token for object type */
int	check_tok(char *input, char **types)
{
	t_i	i;

	i.x = 0;

	if (input[0] == '#')														/* If a comment line is found, ignore the line entirely */
		return (-2);
	while (types[i.x])
	{
		if (!ft_strcmp(input, types[i.x]))										/* If valid object type identifier found, return index to access function pointer array */
			return (i.x);
		i.x++;
	}
	return (-1);
}

/* Check each scene element for validity */
int check_scene(t_parse *dat)
{
	t_i	i;
	int	res;

	i.x = -1;
	while (dat->scene[++i.x])
	{
		res = check_tok(dat->scene[i.x][0], dat->tok);							/* Check type identifier against token array */
		if (res == -2)															/* Ignore comment and continue */
			continue;
		if (res == -1)															/* Return error if no type match */
			return (parse_error(dat, PARSE_ERR_OBJ, dat->scene[i.x]));
		if ((res == 0 && dat->has_ambient) || (res == 1 && dat->has_camera))	/* Handle duplicate scene object error */
			return (parse_error(dat, PARSE_ERR_DUP, dat->scene[i.x]));
		if (res == 0 && !dat->has_ambient)
			dat->has_ambient = true;
		if (res == 1 && !dat->has_camera)
			dat->has_camera = true;
		if (res == 6 && !BONUS)													/* Handle bonus object without bonus error */
			return (parse_error(dat, PARSE_ERR_BONUS, dat->scene[i.x]));
		if (!dat->f[res](dat->scene[i.x]))										/* Call correct parse function for object */
			return (parse_error(dat, PARSE_ERR_BAD_DATA, dat->scene[i.x]));
	}
	return (1);
}

/* Parse .rt scene file to ensure data is valid */
int	parse(t_data *rt, char *path)
{
	init_parse(&rt->parse);
	if (!open_scene(&rt->parse, path) || !check_scene(&rt->parse))
		return (0);
	return (1);
}
