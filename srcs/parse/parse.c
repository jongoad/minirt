#include "minirt.h"

/* Free all allocated memory used for parsing */
void	parse_free(t_parse *dat)
{
	t_i i;

	i.x = 0;
	if (dat->buf)
		free(dat->buf);
	if (dat->split)
		ft_free_split(dat->split);
	if (dat->scene)
	{
		while (dat->scene[i.x])
		{
			ft_free_split(dat->scene[i.x]);
			i.x++;
		}
		free(dat->scene);
	}
	if (dat->tok)
		ft_free_split(dat->tok);
}

/* Free parse memory on error return */
int	parse_error(t_parse *dat, char *err)
{
	ft_putstr_fd(err, 2);
	parse_free(dat);
	return (0);
}

/* Allocate, initilialize, and return token array */
char	**create_tok(void)
{
	char **tok;
	
	tok = ft_xalloc(sizeof(char *) * 7);
	tok[0] = ft_strdup("A");
	tok[1] = ft_strdup("C");
	tok[2] = ft_strdup("L");
	tok[3] = ft_strdup("pl");
	tok[4] = ft_strdup("sp");
	tok[5] = ft_strdup("cy");
	tok[6] = NULL;
	return (tok);
}

/* Split individual scene lines by space */
void	split_scene(t_parse *dat)
{
	t_i i;

	i.x = 0;
	while (dat->split[i.x])
		i.x++;
	dat->scene = ft_xalloc(sizeof(char *) * (i.x + 1));
	i.x = 0;
	while(dat->split[i.x])
	{
		dat->scene[i.x] = ft_split(dat->split[i.x], ' ');
		i.x++;
	}
	dat->scene[i.x] = NULL;
}

/* Setup parse variables */
void init_parse(t_parse *dat)
{
	dat->buf = NULL;
	dat->scene = NULL;
	dat->split = NULL;
	dat->f[0] = parse_ambient;
	dat->f[1] = parse_camera;
	dat->f[2] = parse_light;
	dat->f[3] = parse_plane;
	dat->f[4] = parse_sphere;
	dat->f[5] = parse_cylinder;
	dat->tok = create_tok();
	dat->has_ambient = false;
	dat->has_camera = false;
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
		return (parse_error(dat, PARSE_ERR_OPEN));
	dat->buf = ft_xalloc(READ_SIZE + 1);
	status = read(dat->fd, dat->buf, READ_SIZE);
	if (status == -1)
		return (parse_error(dat, PARSE_ERR_READ));
	dat->split = ft_split(dat->buf, '\n');
	while (dat->split && dat->split[i])
		i++;
	if (i == 0)
		return (parse_error(dat, PARSE_ERR_EMPTY));
	replace_whitespace(dat);
	split_scene(dat);
	return (1);
}

/* Attempt to match token for object type */
int	check_tok(char *input, char **types)
{
	t_i i;

	i.x = 0;

	if (input[0] == '#')
		return (-2);
	while (types[i.x])
	{
		if (!ft_strcmp(input, types[i.x]))
			return (i.x);
		i.x++;
	}
	return (-1);
}

/* Check each scene element for validity */
int check_scene(t_parse *dat)
{
	t_i		i;
	int		res;

	i.x = -1;
	while (dat->scene[++i.x])
	{
		res = check_tok(dat->scene[i.x][0], dat->tok);
		if (res == -2)
			continue;
		if (res == -1)
			return (parse_error(dat, PARSE_ERR_OBJ));
		if ((res == 0 && dat->has_ambient) || (res == 1 && dat->has_camera))
			return (parse_error(dat, PARSE_ERR_DUP));
		if (res == 0 && !dat->has_ambient)
			dat->has_ambient = true;
		if (res == 1 && !dat->has_camera)
			dat->has_camera = true;
		if (!dat->f[res](dat->scene[i.x]))
			return (parse_error(dat, PARSE_ERR_BAD_DATA));
	}
	return (1);
}


/* Check if scene if valid */
int	parse(t_data *rt, char *path)
{
	init_parse(&rt->parse);
	if (!open_scene(&rt->parse, path) || !check_scene(&rt->parse))
		return (0);
	
	return (1);
}
