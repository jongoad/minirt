#include "minirt.h"

/* Skip a commented line */
void	parse_ppm_skip_comment(char *buf, int *p)
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

/* Write a single pixel from .ppm image to array */
void	write_ppm_color(t_color *pixel, char *buf, int *p)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (i == 0)
			pixel->r = buf[(*p)];
		else if (i == 1)
			pixel->g = buf[(*p)];
		else if (i == 2)
			pixel->b = buf[(*p)];
		(*p)++;
		i++;
	}
}

/* Parse .ppm file data and read into memory */
int	parse_ppm(t_ppm *img, char *buf)
{
	t_i	i;
	int	p;

	p = 0;
	img->type = parse_ppm_identifier(buf, &p);
	if (!img->type)
		return_on_err(PPM_ERR_TYPE, 0);
	parse_ppm_header(img, buf, &p);
	img->pixels = ft_xalloc(sizeof(t_color *) * img->height);
	i.y = 0;
	while (i.y < img->height)
	{
		i.x = 0;
		img->pixels[i.y] = ft_xalloc(sizeof(t_color) * img->width);
		while (i.x < img->width)
		{
			write_ppm_color(&img->pixels[i.y][i.x], buf, &p);
			i.x++;
		}
		i.y++;
	}
	return (1);
}

/* Open a .ppm image file. Parse it and read into memory */
int	read_ppm(t_ppm *img, char *path)
{
	int		fd;
	int		status;
	char	*buf;

	buf = ft_xalloc(READ_SIZE + 1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return_on_err_ppm(PPM_ERR_OPEN, fd, buf, path);
	status = read(fd, buf, READ_SIZE);
	if (status == -1)
		return_on_err_ppm(PPM_ERR_READ, fd, buf, path);
	buf[status] = '\n';
	if (!parse_ppm(img, buf))
		return_on_err_ppm(PPM_ERR_PARSE, fd, buf, path);
	close(fd);
	free(buf);
	return (1);
}
