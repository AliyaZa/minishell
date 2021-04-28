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

// char	*ft_take_word2(char *string)
// {
// 	int		index;
// 	char	*p;
// 	int		start;
// 	char	flag;

// 	p = string;
// 	index = 0;
// 	flag = '\0';
// 	while (p[index] == ' ' && !flag)
// 	{
// 		index++;
// 		if (p[index] == '"' || p[index] == '\'')
// 			flag = p[index];
// 	}
// 	start = index;
// 	while (p[index] && ft_isprint(p[index]) && p[index] != ' ')
// 		index++;
// 	string = &p[index];
// 	return (ft_substr(p, start, index));
// }