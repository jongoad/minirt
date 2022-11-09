#ifndef ERROR_H_
# define ERROR_H_

/* Error Message Defines */
#define BAD_ARG_ERR "Usage: ./minirt [path-to-scene-file]\n"

/* Parse Errors*/
#define PARSE_ERR_OPEN "Error: unable to open specified file\n"
#define PARSE_ERR_READ "Error: unable to read specified file\n"
#define PARSE_ERR_EMPTY "Error: specified file is empty\n"
#define PARSE_ERR_OBJ "Error: invalid scene object\n"
#define PARSE_ERR_DUP "Error: duplicate camera or ambient light objects\n"
#define PARSE_ERR_BAD_DATA "Error: scene object contains invalid data\n"
#define PARSE_ERR_BONUS "Error: object type only valid in bonus\n"
#define PARSE_ERR_FLOAT "Error: float value is out of defined range or invalid\n"
#define PARSE_ERR_INT "Error: int value is out of defined range\n"
#define PARSE_ERR_ORIENT "Error: orientation values are out of defined range or invalid\n"
#define PARSE_ERR_POS "Error: invalid coordinate data for object\n"

/* PPM Image Errors */
#define PPM_ERR_OPEN "Error: unable to open image file:\n"
#define PPM_ERR_READ "Error: unable to open image file:\n"
#define PPM_ERR_PARSE "Error: image file contains invalid data:\n"
#define PPM_ERR_TYPE "Error: image filetype is not valid\n"
#endif

