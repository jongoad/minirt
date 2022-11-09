#include "minirt.h"

/* Confirm valid "magic number" identifier */
int parse_ppm_identifier(char *buf, int *p)
{
	int ret;

	ret = 0;
	if (buf[*p])													/* Check for "Magic Number" identifier P6 or P3*/
	{
		if (buf[*p] != 'P')
			return (0);
		(*p)++;
	}
	if (buf[*p])
	{
		if (buf[*p] == '6')
			ret = 6;
		else if (buf[*p] == '3')
			ret = 3;
		(*p)++;
	}
	parse_ppm_skip_whitespace(buf, p);
	if (buf[*p] && buf[*p] == '#')
		parse_ppm_skip_comment(buf, p);
	return (ret);
}

/* Get image width */
void parse_ppm_width(t_ppm *img, char *buf, int *p)
{
	while (buf[*p] && !ft_isdigit(buf[*p]))
	{
		if (buf[*p] == '#')
			parse_ppm_skip_comment(buf, p);
		else if (buf[*p] && (ft_isspace(buf[*p]) || buf[*p] == '\n'))
			parse_ppm_skip_whitespace(buf, p);		
	}
	img->width = ft_atoi(&buf[*p]);
	while (buf[*p] && ft_isdigit(buf[*p]))
		(*p)++;
}

/* Get image height */
void parse_ppm_height(t_ppm *img, char *buf, int *p)
{
	while (buf[*p] && !ft_isdigit(buf[*p]))
	{
		if (buf[*p] == '#')
			parse_ppm_skip_comment(buf, p);
		else if (buf[*p] && (ft_isspace(buf[*p]) || buf[*p] == '\n'))
			parse_ppm_skip_whitespace(buf, p);	
	}
	img->height= ft_atoi(&buf[*p]);
	while (buf[*p] && ft_isdigit(buf[*p]))
		(*p)++;
}

/* Get image maxval */
void parse_ppm_maxval(t_ppm *img, char *buf, int *p)
{
	while (buf[*p] && !ft_isdigit(buf[*p]))
	{
		if (buf[*p] == '#')
			parse_ppm_skip_comment(buf, p);
		else if (buf[*p] && (ft_isspace(buf[*p]) || buf[*p] == '\n'))
			parse_ppm_skip_whitespace(buf, p);	
	}
	img->maxval= ft_atoi(&buf[*p]);
	while (buf[*p] && ft_isdigit(buf[*p]))
		(*p)++;
}

/* Parse header info (width, height, maxval) */
void parse_ppm_header(t_ppm *img, char *buf, int *p)
{
	parse_ppm_width(img, buf, p);									/* Get the width of the image*/							
	parse_ppm_height(img, buf, p);									/* Get the height of the image*/
	parse_ppm_maxval(img, buf, p);									/* Get the maximum colour value of the image */
	if (buf[*p] == '\n')											/* Increment past last byte before binary data starts*/
		(*p)++;
}
