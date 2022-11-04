#include "minirt.h"

/* Skip a commented line */
void parse_ppm_skip_comment(char *buf, int *p)
{
	while (buf[*p] && buf[*p] != '\n')
		(*p)++;
	if (buf[*p] == '\n')
		(*p)++;
}

/* Skip whitespace */
void	parse_ppm_skip_whitespace(char *buf, int *p)
{
	while (buf[*p] && (ft_isspace(buf[*p]) || buf[*p] == '\n'))
		(*p)++;
}

/* Confirm valid "magic number" identifier */
int parse_ppm_identifier(char *buf, int *p)
{
	int ret;

	ret = 0;
	if (buf[*p])
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
	parse_ppm_width(img, buf, p);
	parse_ppm_height(img, buf, p);
	parse_ppm_maxval(img, buf, p);
	/* Increment past last byte before binary data starts*/
	if (buf[*p] == '\n')
		(*p)++;
}

int	parse_ppm(t_ppm *img, char *buf)
{
	t_i i;
	int p;

	p = 0;
	img->type = parse_ppm_identifier(buf, &p);
	if (!img->type)
		return (0); /* Return error not valid .ppm file */
	parse_ppm_header(img, buf, &p);
	img->pixels = ft_xalloc(sizeof(t_color *) * img->height);
	i.y = 0;

	while (i.y < img->height)
	{
		i.x = 0;
		img->pixels[i.y] = ft_xalloc(sizeof(t_color) * img->width);
		while (i.x < img->width)
		{
			i.z = 0;
			while (i.z < 3)
			{
					if (i.z == 0)
						img->pixels[i.y][i.x].r = buf[p];
					else if (i.z == 1)
						img->pixels[i.y][i.x].g = buf[p];
					else if (i.z == 2)
						img->pixels[i.y][i.x].b = buf[p];
					p++;
					i.z++;
			}
			i.x++;
		}
		i.y++;
	}
	return (1);
}



int	read_ppm(t_ppm *img, char *path)
{
	int 	fd;
	int 	status;
	char	*buf;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0); // Return error
	buf = ft_xalloc(READ_SIZE + 1);
	status = read(fd, buf, READ_SIZE);
	if (status == -1)
		return (0); // Return error
	close(fd);
	free(buf);
	if (!parse_ppm(img, buf))
		return (0);
	return (1);
}