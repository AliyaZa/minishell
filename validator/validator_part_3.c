/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_part_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:18:38 by mismene           #+#    #+#             */
/*   Updated: 2021/05/06 21:18:40 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*validate_quote(char *quote, char *p, size_t index)
{
	char	*validated;

	if (!(*quote) || p[index] == *quote)
	{
		if (!(*quote))
			*quote = p[index];
		else if (p[index] == *quote)
			*quote = '\0';
		ft_delete_char(&p, index);
	}
	validated = ft_strdup(p);
	free(p);
	return (validated);
}

void	insert_value(char *value, char **tmp, char *tmp1)
{
	if (value)
	{
		*tmp = ft_strjoin(*tmp, value);
		*tmp = ft_strjoin(*tmp, tmp1);
		free(tmp1);
	}
}

char	*validate_env_sub(char quote, char *p, size_t index, t_env *env)
{
	size_t	i;
	char	*value;
	int		kc;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(p, 0, index);
	tmp1 = ft_substr(p, (ft_strlen_cc(&p[index],
		' ', '"')) + index, ft_strlen(p));
	i = index;
	kc = 0;
	while (p[i] != ' ' && p[i] != '"' && p[i] != '\'' && p[i] != quote)
	{
		kc++;
		i++;
	}
	value = get_value_by_key(env, ft_substr(p, index + 1, kc - 1));
	insert_value(value, &tmp, tmp1);
	return (tmp);
}

char	*mirroring(char *p, char quote)
{
	if (!quote)
		ft_delete_char(&p, 0);
	else if (quote == '"')
	{
		if (!ft_isalpha(*(p + 1)))
		{
			ft_delete_char(&p, 0);
		}
	}
	return (p);
}
