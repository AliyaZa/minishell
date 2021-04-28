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