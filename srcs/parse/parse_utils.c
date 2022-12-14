#include "minirt.h"

/* Replace all whitespaces with space char */
void	replace_whitespace(t_parse *dat)
{
	t_i i;

	i.y = 0;
	while (dat->split[i.y])
	{
		i.x = 0;
		while (dat->split[i.y][i.x])
		{
			if (is_set(dat->split[i.y][i.x], "\t\v\f\r"))				/* If non space character whitespace is found, replace with space character */
				dat->split[i.y][i.x] = ' ';
			i.x++;
		}
		i.y++;
	}
}

/* Free parse memory on error return */
int	parse_error(t_parse *dat, char *err, char **line)
{
	t_i i;

	i.x = 0;
	ft_putstr_fd(err, 2);
	if (line)															/* If line is provided, print line where error occured */
	{
		ft_putchar_fd('\t', 2);
		while (line[i.x])
		{
			ft_putstr_fd(line[i.x], 2);
			if (line[i.x + 1])
				ft_putstr_fd(" ", 2);
			i.x++;
		}
	}
	parse_free(dat);													/* Free parse data before return */
	return (0);
}

/* Free all allocated memory used for parsing */
void	parse_free(t_parse *dat)
{
	t_i i;

	i.x = 0;
	if (dat->buf)														/* Free read buffer */
		free(dat->buf);
	if (dat->split)														/* Free scene line split */
		ft_free_split(dat->split);
	if (dat->scene)														/* Free object component split */
	{
		while (dat->scene[i.x])
		{
			ft_free_split(dat->scene[i.x]);
			i.x++;
		}
		free(dat->scene);
	}
	if (dat->tok)														/* Free identifier token array */
		ft_free_split(dat->tok);
	close(dat->fd);
}

/* Split individual scene lines by space */
void	split_scene(t_parse *dat)
{
	t_i i;

	i.x = 0;
	while (dat->split[i.x])
		i.x++;
	dat->scene = ft_xalloc(sizeof(char *) * (i.x + 1));
	i.x = 0;
	while(dat->split[i.x])
	{
		dat->scene[i.x] = ft_split(dat->split[i.x], ' ');				/* Split each scene object into components */
		i.x++;
	}
	dat->scene[i.x] = NULL;
}

/* Allocate, initilialize, and return token array */
char	**create_tok(void)
{
	char	**tok;
	
	tok = ft_xalloc(sizeof(char *) * 8);
	tok[0] = ft_strdup("A");
	tok[1] = ft_strdup("C");
	tok[2] = ft_strdup("L");
	tok[3] = ft_strdup("pl");
	tok[4] = ft_strdup("sp");
	tok[5] = ft_strdup("cy");
	tok[6] = ft_strdup("co");
	tok[7] = NULL;
	return (tok);
}
