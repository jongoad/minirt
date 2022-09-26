#include "../../includes/minirt.h"

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
	dat->f[0] = parse_ambient;
	dat->f[1] = parse_camera;
	dat->f[2] = parse_light;
	dat->f[3] = parse_plane;
	dat->f[4] = parse_sphere;
	dat->f[5] = parse_cylinder;
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
	replace_whitespace(dat);
	split_scene(dat);
	return (1);
}

/* Attempt to match token for object type */
int	check_tok(char *input, char **tok)
{
	t_i i;

	i.x = 0;

	while (tok[i.x])
	{
		if (!ft_strcmp(input, tok[i.x]))
			return (i.x);
		i.x++;
	}
	return (-1);
}

/* Check each scene element for validity */
int check_scene(t_parse *dat)
{
	t_i i;
	int res;
	char **tok;
	
	tok = ft_xalloc(sizeof(char *) * 7);
	tok[0] = ft_strdup("A");
	tok[1] = ft_strdup("C");
	tok[2] = ft_strdup("L");
	tok[3] = ft_strdup("pl");
	tok[4] = ft_strdup("sp");
	tok[5] = ft_strdup("cy");
	tok[6] = NULL;
	i.x = 0;

	/* Check initial inputs */
	t_i p;

	p.x = 0;
	p.y = 0;

	while (dat->scene[p.y])
	{
		p.x = 0;
		printf("Object type is: %s\n", dat->scene[p.y][0]);
		while (dat->scene[p.y][p.x])
		{
			printf("%s\n", dat->scene[p.y][p.x]);
			p.x++;
		}
		printf("\n\n");
		p.y++;
	}

	printf("-------------------------------------\n\n");


	//Check first field of each line to match token
	while (dat->scene[i.x])
	{
		printf("%s\n", dat->scene[i.x][0]);
		res = check_tok(dat->scene[i.x][0], tok);
		printf("Res: %i\n", res);
		if (res == -1)
			return (0);
		if (!dat->f[res](dat->scene[i.x]))
			return (0);
		i.x++;
		printf("\n\n");
	}
	return (1);
}

/* Check if scene if valid */
int	parse(t_data *rt, char *path)
{
	t_parse dat;

	(void)rt;

	init_parse(&dat);
	if (!open_scene(&dat, path) || !check_scene(&dat))
		return (0);
	else
		return (1);
		
	// init_scene(rt, &dat);
}

// /* Create objects based on parse data */
// void	init_scene(t_data *rt, t_parse *dat)
// {
// 	//Count number of objects

// 	//Allocate space for objects

// 	//Populate data
// }
