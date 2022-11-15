#include "minirt.h"

/* Memory safe allocation */
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

/* Error messaging & exit */
void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit(EXIT_FAILURE);
}

/* Count number of elements in a 2D string array */
int	count_array_2d(char **array)
{
	t_i	i;

	i.x = 0;
	while (array && array[i.x])
		i.x++;
	return (i.x);
}

/* Print program controls to terminal */
void	print_usage(void)
{
	printf("%s\n*** Object Rotations ***\n%s", BASH_CYAN, BASH_RESET);
	printf("x axis:   `1' // `2'\n");
	printf("y axis:   `4' // `5'\n");
	printf("z axis:   `7' // `8'\n");
	printf("Toggle All:  'R'\n");
	printf("%s\n*** Object Translations ***\n%s", BASH_CYAN, BASH_RESET);
	printf("x axis:   KEY_LEFT / 'A' 		// KEY_RIGHT / 'D'\n");
	printf("y axis:   KEY_UP / KEY_Z 		// KEY_DOWN / KEY_X\n");
	printf("z axis:   MOUSE_WHEEL_UP / 'W'  // MOUSE_WHEEL_UP / 'D' \n");
	printf("%s\n*** Object Scale ***\n%s", BASH_CYAN, BASH_RESET);
	printf("scale:		 '+' // '-' \n");
	printf("%s\n*** Fun stuff ***\n%s", BASH_CYAN, BASH_RESET);
	printf("Print usage:	  			   KEY_F1\n");
	printf("Print selected obj info:	   SPACEBAR\n");
	if (BONUS)
	{
		printf("Toggle Light Halos:  'L'\n");
		printf("Toggle texture on/off:	   KEY_T\n");
		printf("Toggle normal on/off:	   KEY_N\n");
	}
}

/* Print error message and return value */
int	return_on_err(char *err_msg, int retval)
{
	ft_putstr_fd(err_msg, 2);
	return (retval);
}
