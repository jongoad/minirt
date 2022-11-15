/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:12:56 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 15:12:58 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Load and initialize texture from image file */
void	init_texture(t_obj *obj, char *input)
{
	if (!ft_strcmp(input, "checkers"))
	{
		if (obj->type == T_SPH)
			obj->texture = uv_checkers(16, 8,
					int_to_color(BLACK), int_to_color(WHITE));
		else
			obj->texture = uv_checkers(8, 8,
					int_to_color(BLACK), int_to_color(WHITE));
		obj->texture.is_checkers = true;
	}
	else if (!read_ppm(&obj->texture.image, input))
		return ;
	else
	{
		obj->texture.is_image = true;
		obj->texture.width = obj->texture.image.width;
		obj->texture.height = obj->texture.image.height;
	}
}

/* Load and initialize normal map from image file*/
void	init_normal(t_obj *obj, char *input)
{
	obj->normal.is_image = false;
	if (!read_ppm(&obj->normal.image, input))
		return ;
	else
	{
		obj->normal.is_image = true;
		obj->normal.width = obj->normal.image.width;
		obj->normal.height = obj->normal.image.height;
	}
}

/* Initialize bonus attributes for objects */
void	init_obj_bonus(t_obj *obj, char **input)
{
	char	**split;
	t_i		i;

	i.x = 0;
	while (input[i.x])
	{
		split = ft_split(input[i.x], ':');
		if (split[0] && split[1])
		{
			if (!ft_strcmp(split[0], "texture"))
				init_texture(obj, split[1]);
			else if (!ft_strcmp(split[0], "normal"))
				init_normal(obj, split[1]);
			else if (!ft_strcmp(split[0], "shininess"))
				obj->shininess = ft_atof(split[1]);
		}
		ft_free_split(split);
		i.x++;
	}
}
