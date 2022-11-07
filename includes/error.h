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

#endif

