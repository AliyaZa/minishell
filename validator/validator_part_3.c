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
	char	*tmp;
	char	*tmp1;
	char	*validated;

	tmp = NULL;
	tmp1 = NULL;
	if (!(*quote) || p[index] == *quote)
	{
		if (!(*quote))
			*quote = p[index];
		else if (p[index] == *quote)
			*quote = '\0';
		tmp = ft_substr(p, 0, index);
		tmp1 = ft_substr(p, index + 1, ft_strlen(p));
	}
	validated = ft_strjoin(tmp, tmp1);
	free_str(&tmp);
	free_str(&tmp1);
	free(p);
	return (validated);
}

char	*validate_env_sub(char quote, char *p, size_t index, t_env *env)
{
	size_t	i;
	char	*value;
	int		kc;
	char	*tmp;
	char	*tmp1;
	char	*free;

	tmp = ft_substr(p, 0, index);
	tmp1 = ft_substr(p, (ft_strlen_cc(&p[index],
		' ', '"')) + index, ft_strlen(p));
	i = index;
	kc = 0;
	free = NULL;
	while (p[i] != ' ' && p[i] != '"' && p[i] != '\'' && p[i] != quote)
	{
		kc++;
		i++;
	}
	value = get_value_by_key(env, ft_substr(p, index + 1, kc - 1));
	if (value)
	{
		free = tmp;
		tmp = ft_strjoin(tmp, value);
		free_str(&free);
	}
	free = tmp;
	tmp = ft_strjoin(tmp, tmp1);
	free_str(&free);
	free_str(&tmp1);
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
