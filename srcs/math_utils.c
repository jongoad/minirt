/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:14:42 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 15:14:43 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Convert degrees to radians */
float	deg_to_rad(float deg)
{
	return (deg * (PI / 180));
}

/* Round a float at a specified precision */
float	roundf_precision(float n, float p)
{
	double	res;

	res = round(n * p);
	return (res / p);
}
