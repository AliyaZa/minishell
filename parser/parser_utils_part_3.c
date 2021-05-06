#include "../minishell.h"

void		validate_q(char *quote, char *p, size_t index)
{
	if (*quote == 0)
		*quote = p[index];
	else if (*quote == p[index])
		*quote = 0;
}

void		validate_pipe(char **raw_string)
{
	size_t	index;
	char	quote;
	char	*p;

	p = *raw_string;
	index = 0;
	quote = '\0';
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
			validate_q(&quote, p, index);
		else if (p[index] == '|' && quote)
			p[index] = -1;
		else if (p[index] == '\\')
			p[index + 1] = -1;
		index++;
	}
}

void		validate_spaces(char **string)
{
	char	*p;
	size_t	index;
	char	quote;

	quote = '\0';
	p = *string;
	index = 0;
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
			validate_q(&quote, p, quote);
		else if (p[index] == ' ' && quote)
			p[index] = -1;
		index++;
	}
}

void		replace_symbol3(char ****array, char old, char new)
{
	char	***p;
	size_t	index;

	p = *array;
	index = 0;
	while (p[index])
	{
		replace_symbol_array(p, old, new);
		index++;
	}
}

char		***get_pipes(t_command *command)
{
	char	**matrix;
	char	***pipes;
	size_t	i;
	char	*p;

	i = 0;
	p = ft_strdup(command->raw_string);
	if (ft_strchr(command->raw_string, '|'))
		command->flags->pipe = 1;
	validate_pipe(&p);
	matrix = ft_split(p, '|');
	replace_symbol_array(&matrix, -1, '|');
	pipes = (char ***)malloc(sizeof(char **) * array_size(matrix));
	while (matrix[i])
	{
		validate_spaces(&matrix[i]);
		pipes[i] = ft_split(matrix[i], ' ');
		replace_symbol3(&pipes, -1, ' ');
		i++;
	}
	return (pipes);
}
