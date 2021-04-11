#include "minishell.h"

void	substitution(char **dst, t_env *env)
{
	int		index;
	char	*key;
	char	*string;
	char	*value;
	char	*rest;
	char	*start;

	index = 0;
	string = *dst;
	key = NULL;
	value = NULL;
	rest = NULL;
	if (ft_strchr(string, '$'))
		start = ft_strdup2(string, '$');
	while (*string)
	{
		if (*string == '$')
		{
			string++;
			key = ft_strdup(string);
			break ;
		}
		string++;
	}

	if (key)
	{
		while (ft_isalpha(key[index]) && key[index] != ' ' && key[index])
		{
			index++;
		}
		rest = ft_strdup(&key[index]);
		key[index] = 0;
		value = get_value_by_key(env, key);
	}
	start = ft_strjoin2(start, value);
	start = ft_strjoin2(start, rest);
	if (start && ft_strchr(start, '$'))
		substitution(&start, env);
	free_str(dst);
	*dst = ft_strdup(start);
	free(start);
}