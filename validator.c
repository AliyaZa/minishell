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

	index = 0;
	start = *string;
	save = NULL;
	flag = 0;
	(void)env->key;
	while (*start)
	{
		if (start[index] == '"' || start[index] == '\'')
		{
			if (!flag)
				flag = start[index];
			else
			{
				if (flag == start[index])
				{
					flag = 0;
				}
			}
			start[index] = 0;
			save = ft_strdup(&start[index + 1]);
			*string = ft_strjoin(*string, save);
			start = *string;
		}
		start++;
	}
	if (flag == '"')
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file", 1);
	}
}
