#include "../minishell.h"

char	*validate_quote(char *quote, char *p, size_t index)
{
	char	*tmp;
	char	*tmp1;

	if (!(*quote) || p[index] == *quote)
	{
		if (!(*quote))
			*quote = p[index];
		else if (p[index] == *quote)
			*quote = '\0';
		tmp = ft_substr(p, 0, index);
		tmp1 = ft_substr(p, index + 1, ft_strlen(p));
	}
	return (ft_strjoin(tmp, tmp1));
}

char	*validate_env_sub(char quote, char *p, size_t index, t_env *env)
{
	size_t	i;
	char	*value;
	int		kc;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(p, 0, index);
	tmp1 = ft_substr(p, (ft_strlen_cc(&p[index], ' ', '"')) + index, ft_strlen(p));
	i = index;
	kc = 0;
	while (p[i] != ' ' && p[i] != '"' && p[i] != '\'' && p[i] != quote)
	{
		kc++;
		i++;
	}
	value = get_value_by_key(env, ft_substr(p, index + 1, kc - 1));
	if (value)
		tmp = ft_strjoin_free(tmp, value, 1);
	tmp = ft_strjoin_free(tmp, tmp1, 3);
	return (tmp);
}
