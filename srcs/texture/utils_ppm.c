#include "minirt.h"

/* Return error and print read_ppm specific errors */
int	return_on_err_ppm(char *err, int fd, char *buf, char *path)
{
	ft_putstr_fd(err, 2);
	fprintf(stderr, "\tpath: %s\n", path);
	free(buf);
	close(fd);
	return (0);
}
