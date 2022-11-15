/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:04:35 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 15:06:06 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define RED_C "\033[1;31m"
#define CLEAR "\033[0m"

/* Print out current data for an individual object */
void	print_obj_data(t_obj *obj)
{
	printf(RED_C"------- Selected Object Data -------\n\n"CLEAR);
	printf ("\tType: %c\n", obj->type);
	printf("\tRadius: %f\n", obj->radius);
	printf("\tWidth: %f\n", obj->width);
	printf("\tHeight: %f\n\n", obj->half_height);
	printf(RED_C"--- Position ---\n"CLEAR);
	printf("\tx: %f\n\ty: %f\n\tz: %f\n\n", obj->pos.x, obj->pos.y, obj->pos.z);
	printf(RED_C"--- Orientation ---\n"CLEAR);
	printf("\tx: %f\n\ty: %f\n\tz: %f\n\n", obj->fwd.x, obj->fwd.y, obj->fwd.z);
	printf(RED_C"--- Color ---\n"CLEAR);
	printf("\tr: %d\n\tg: %d\n\tb: %d\n\n", obj->clr.r, obj->clr.g, obj->clr.b);
}
