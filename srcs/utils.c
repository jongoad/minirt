#include "minirt.h"

void	*ft_xalloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit (EXIT_FAILURE);
	}
	return (mem_space);
}

void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit(EXIT_FAILURE);
}
