#include "minishell.h"

size_t	matrixlen(char **matrix)
{
	size_t	counter;

	counter = 0;
	printf("%lu\n", sizeof(char **));
	while (matrix[counter])
	{
		ft_putstr_fd(matrix[counter], 1);
		counter++;
	}
	return (counter);
}