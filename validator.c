/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:04:00 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 14:45:58 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validator(char **string, t_env *env)
{
	char	*start;
	int		index;
	char	*save;
	char	flag;
	int		k;
	char	*value;

	index = 0;
	start = *string;
	save = NULL;
	flag = 0;
	k = 0;
	(void)env->key;
	while (*start)
	{
		if (*start == '"' || *start == '\'')
		{
			if (!flag)
				flag = *start;
			else
			{
				if (flag == *start)
				{
					flag = 0;
				}
			}
			*start = 0;
			save = ft_strdup(start + 1);
			*string = ft_strjoin(*string, save);
			free_str(&save);
			start = *string;
		}
		if (*start == '$' && (flag == 0 || flag == '"'))
		{
			*start++ = 0;
			value = get_value_by_key(env, ft_strdup_c(start, ' '));
			save = ft_strdup(start + ft_strlen_c(start, ' '));
			*string = ft_strjoin(*string, value);
			*string = ft_strjoin(*string, save);
			free_str(&save);
			start = *string;
		}
		start++;
	}
	if (flag)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file", 1);
	}
}
