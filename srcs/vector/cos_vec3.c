/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 13:59:15 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Gives you the cos of the angle between two vectors */
double  cos_vec3(t_vec3 a, t_vec3 b)
{
	return dot_vec3(a, b) / (length_vec3(a) * length_vec3(b));
}
