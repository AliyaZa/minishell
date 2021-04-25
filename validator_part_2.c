#include "minishell.h"

void	validate_command(char **command)
{
	size_t	index;
	char	*p;
	char	*start;
	char	*end;
	char	flag;

	p = ft_strdup(*command);
	index = 0;
	flag = 0;
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
		{
			if (!flag)
				flag = p[index];
			else if (flag == p[index])
				flag = 0;
			start = ft_substr(p, 0, index);
			end = ft_substr(p, index + 1, ft_strlen(p));
			p = ft_strjoin(start, end);
			continue ;
		}
		index++;
	}
	*command = ft_strdup(p);
}