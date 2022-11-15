/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:13:51 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 15:35:37 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Parse plane (pl) */
int	parse_plane(char **obj)
{
	t_i	i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x < 4)
		return (0);
	if (!check_coords(obj[1]))
		return (0);
	if (!check_orientation(obj[2]))
		return (0);
	if (!check_rgb(obj[3]))
		return (0);
	if (BONUS && i.x > 4)
	{
		i.x = 4;
		while (obj[i.x])
		{
			if (!parse_obj_bonus(obj[i.x]))
				return (0);
			i.x++;
		}
	}
	return (1);
}

/* Parse sphere (sp) */
int	parse_sphere(char **obj)
{
	t_i	i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x < 4)
		return (0);
	if (!check_coords(obj[1]))
		return (0);
	else if (!check_float(obj[2], 0, 0))
		return (0);
	else if (!check_rgb(obj[3]))
		return (0);
	if (BONUS && i.x > 4)
	{
		i.x = 4;
		while (obj[i.x])
		{
			if (!parse_obj_bonus(obj[i.x]))
				return (0);
			i.x++;
		}
	}
	return (1);
}

/* Parse cylinder (cy) */
int	parse_cylinder(char **obj)
{
	t_i	i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x < 6)
		return (0);
	if (!check_coords(obj[1]) || !check_orientation(obj[2]))
		return (0);
	if (!check_float(obj[3], 0, 0) || !check_float(obj[4], 0, 0))
		return (0);
	if (!check_rgb(obj[5]))
		return (0);
	if (BONUS && i.x > 6)
	{
		i.x = 6;
		while (obj[i.x])
		{
			if (!parse_obj_bonus(obj[i.x]))
				return (0);
			i.x++;
		}
	}
	return (1);
}

/* Parse cone (co) */
int	parse_cone(char **obj)
{
	t_i	i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x < 6)
		return (0);
	else if (!check_coords(obj[1]) || !check_orientation(obj[2]))
		return (0);
	else if (!check_float(obj[3], 1, 75) || !check_float(obj[4], 0.1, 100))
		return (0);
	else if (!check_rgb(obj[5]))
		return (0);
	if (BONUS && i.x > 6)
	{
		i.x = 6;
		while (obj[i.x])
		{
			if (!parse_obj_bonus(obj[i.x]))
				return (0);
			i.x++;
		}
	}
	return (1);
}

/* Parse bonus object attributes */
int	parse_obj_bonus(char *obj)
{
	char	**split;
	int		retval;

	split = ft_split(obj, ':');
	retval = 1;
	if (count_array_2d(split) == 2)
	{
		if (!ft_strcmp(split[0], "shininess"))
			if (!check_float(split[1], 0, MAX_SHININESS))
				retval = 0;
		if (!ft_strcmp(split[0], "texture"))
			if (!check_path(split[1], T_TEXTURE))
				retval = 0;
		if (!ft_strcmp(split[0], "normal"))
			if (!check_path(split[1], T_NORMAL))
				retval = 0;
	}
	else
		retval = 0;
	ft_free_split(split);
	return (retval);
}
