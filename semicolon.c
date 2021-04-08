#include "minishell.h"

void	semicolon(char **string)
{
	char	*p_n;

	if ((p_n = ft_strchr(*string, ';')))
	{
		*p_n++ = 0;
	}
}