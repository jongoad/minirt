#include "minirt.h"

t_data	*get_data(void)
{
	static t_data *data;

	if (!data)
		data = malloc(sizeof(t_data));
	return (data);
}