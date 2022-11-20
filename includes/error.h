/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:31:27 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/20 16:29:54 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* Error Message Defines */
# define BAD_ARG_ERR "Usage: ./minirt [path-to-scene-file]\n"
# define INVALID_SCENE "Error\n\tinvalid scene file type - must be .rt\n"

/* Parse Errors*/
# define PARSE_ERR_OPEN "Error\n\tunable to open specified file\n"
# define PARSE_ERR_READ "Error\n\tunable to read specified file\n"
# define PARSE_ERR_EMPTY "Error\n\tspecified file is empty\n"
# define PARSE_ERR_OBJ "Error\n\tinvalid scene object\n"
# define PARSE_ERR_DUP "Error\n\tduplicate camera or ambient light objects\n"
# define PARSE_ERR_BAD_DATA "Error\n\tscene object contains invalid data\n"
# define PARSE_ERR_BONUS "Error\n\tobject type only valid in bonus\n"
# define PARSE_ERR_FLOAT "Error\n\tfloat val is out of defined range or invalid\n"
# define PARSE_ERR_INT "Error\n\tint value is out of defined range\n"
# define PARSE_ERR_ORIENT "Error\n\torient vals are out of def range or invalid\n"
# define PARSE_ERR_POS "Error\n\tinvalid coordinate data for object\n"
# define PARSE_ERR_MISS "Error\n\tmissing camera or ambient light\n"

/* PPM Image Errors */
# define PPM_ERR_OPEN "Error\n\tunable to open image file:\n"
# define PPM_ERR_READ "Error\n\tunable to open image file:\n"
# define PPM_ERR_PARSE "Error\n\timage file contains invalid data:\n"
# define PPM_ERR_TYPE "Error\n\timage filetype is not valid\n"

#endif