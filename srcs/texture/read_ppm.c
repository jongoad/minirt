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

/* Parse .ppm file data and read into memory */
int	parse_ppm(t_ppm *img, char *buf)
{
	t_i i;
	int p;

	p = 0;
	img->type = parse_ppm_identifier(buf, &p);						/* Ensure filetype is correct */
	if (!img->type)
	{
		ft_putstr_fd(PPM_ERR_TYPE, 2);
		return (0);
	}
	parse_ppm_header(img, buf, &p);									/* Parse header data */
	img->pixels = ft_xalloc(sizeof(t_color *) * img->height);
	i.y = 0;
	while (i.y < img->height)
	{
		i.x = 0;
		img->pixels[i.y] = ft_xalloc(sizeof(t_color) * img->width);
		while (i.x < img->width)
		{
			i.z = 0;
			while (i.z < 3)											/* Read colour data and assign to memory */
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

/* Open a .ppm image file. Parse it and read into memory */
int	read_ppm(t_ppm *img, char *path)
{
	int 	fd;
	int 	status;
	char	*buf;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(PPM_ERR_OPEN, 2);
		fprintf(stderr, "\tpath: %s\n", path);
		return (0);
	}
	buf = ft_xalloc(READ_SIZE + 1);
	status = read(fd, buf, READ_SIZE);
	if (status == -1)
	{
		ft_putstr_fd(PPM_ERR_READ, 2);
		fprintf(stderr, "\tpath: %s\n", path);
		return (0);
	}
	close(fd);
	free(buf);
	if (!parse_ppm(img, buf))
	{
		ft_putstr_fd(PPM_ERR_PARSE, 2);
		fprintf(stderr, "\tpath: %s\n", path);
		return (0);
	}
	return (1);
}