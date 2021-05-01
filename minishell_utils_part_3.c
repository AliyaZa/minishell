#include "minishell.h"

void	print_array(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		printf("%s\n", p[i]);
		i++;
	}
}

void	ft_insert_str(char **string, char *buf, size_t index)
{
	char	*start;
	char	*end;
	
	start = ft_substr(*string, 0, index);
	end = ft_substr(*string, index, ft_strlen(*string));
	start = ft_strjoin(start, buf);
	start = ft_strjoin(start, end);
	*string = ft_strdup(start);
}

void	ft_delete_char(char **string, size_t place)
{
	char	*start;
	char	*end;

	start = ft_substr(*string, 0, place);
	end = ft_substr(*string, place + 1, ft_strlen(*string));
	start = ft_strjoin(start, end);
	*string = start;
}

void	ft_delete_word(char **string, size_t start, size_t size)
{
	size_t	place;

	place = start;
	while (start < size)
	{
		ft_delete_char(string, place);
		start++;
	}
}

void	free_memory(t_parsed_data *parsed_data, t_command *command)
{
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
	free(command);
}
