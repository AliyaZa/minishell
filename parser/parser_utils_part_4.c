#include "../minishell.h"

static void	validate_redirect(char **p, int index)
{
	int		flag;

	flag = 0;
	if ((*p)[index] == '>')
	{
		ft_delete_char(p, index);
		if ((*p)[index] == '>')
			ft_delete_char(p, index);
		while ((*p)[index] && flag != 2)
		{
			ft_delete_char(p, index);
			if (ft_isprint((*p)[index]) && (*p)[index] != ' ' && !flag)
				flag++;
			if (flag == 1 && (*p)[index] == ' ')
				flag++;
		}
	}
	else
		ft_delete_char(p, index);
}

char		**get_splitted(char *raw_string)
{
	char	*p;
	size_t	index;
	char	quote;
	int		flag;

	p = raw_string;
	quote = '\0';
	index = 0;
	flag = 0;
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
		{
			if (!quote)
				quote = p[index];
			else if (quote == p[index])
				quote = 0;
		}
		if ((p[index] == '>' || p[index] == '<') && !quote)
			validate_redirect(&p, index--);
		index++;
	}
	return (ft_split(p, ' '));
}
