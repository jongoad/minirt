/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normfail.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:03:59 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 16:04:49 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMFAIL_H
# define NORMFAIL_H

typedef struct s_texture	t_texture;
typedef struct s_color		t_color;

t_texture	uv_checkers(int width, int height, t_color c1, t_color c2);

#endif