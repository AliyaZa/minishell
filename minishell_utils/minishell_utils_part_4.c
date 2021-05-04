#include "../minishell.h"

size_t	array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char ***array)
{
	size_t	i;
	char	**p;

	p = *array;
	i = 0;
	while (p[i])
	{
		free_str(&p[i]);
		i++;
	}
	free(array);
}
