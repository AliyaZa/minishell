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

void	print_array3(char ***array)
{
	int		i;
	int		ii;

	i = 0;
	while (array[i])
	{
		printf("%i\n", i);
		ii = 0;
		while (array[i][ii])
		{
			printf("%s\n", array[i][ii]);
			ii++;
		}
		printf("\n");
		i++;
	}
}
