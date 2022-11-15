/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:14:04 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 15:57:20 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Initialize parse variables */
void	init_parse(t_parse *dat)
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
	dat->f[6] = parse_cone;
	dat->tok = create_tok();
	dat->has_ambient = false;
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
	ft_bzero(dat->buf, READ_SIZE + 1);
	status = read(dat->fd, dat->buf, READ_SIZE);
	if (status == -1)
		return (parse_error(dat, PARSE_ERR_READ, NULL));
	dat->split = ft_split(dat->buf, '\n');
	while (dat->split && dat->split[i])
		i++;
	if (i == 0)
		return (parse_error(dat, PARSE_ERR_EMPTY, NULL));
	replace_whitespace(dat);
	split_scene(dat);
	return (1);
}

/* Attempt to match token for object type */
int	check_tok(char *input, char **types)
{
	t_i	i;

	i.x = 0;
	if (!input)
		return (-1);
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
int	check_scene(t_parse *dat)
{
	t_i	i;
	int	res;

	i.x = -1;
	while (dat->scene[++i.x])
	{
		res = check_tok(dat->scene[i.x][0], dat->tok);
		if (res == -2)
			continue ;
		if (res == -1)
			return (parse_error(dat, PARSE_ERR_OBJ, dat->scene[i.x]));
		if ((res == 0 && dat->has_ambient) || (res == 1 && dat->has_camera))
			return (parse_error(dat, PARSE_ERR_DUP, dat->scene[i.x]));
		if (res == 0 && !dat->has_ambient)
			dat->has_ambient = true;
		if (res == 1 && !dat->has_camera)
			dat->has_camera = true;
		if (res == 6 && !BONUS)
			return (parse_error(dat, PARSE_ERR_BONUS, dat->scene[i.x]));
		if (!dat->f[res](dat->scene[i.x]))
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
