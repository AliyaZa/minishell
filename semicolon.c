#include "minishell.h"

void	semicolon(t_command **command)
{
	char	*string;
	int		index;
	int		counter;

	string = (*command)->raw_string;
	index = 0;
	counter = 0;
	while (string[index])
	{
		if (string[index] == ';')
		{
			counter++;
			string[index] = 0;
			(*command)->queue= &string[index + 1];
			break ;
		}
		index++;
	}
	if (!counter)
	{
		(*command)->queue = NULL;
	}
}