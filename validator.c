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

void	validator(char **string, t_env *env, t_command *command)
{
	char	*tmp;
	char	*tmp1;
	char	*p;
	int		index;
	char	flag;

	index = 0;
	p = *string;
	tmp1 = NULL;
	(void)(env->key);
	(void)(command->command);
	flag = 0;
	while (p[index])
	{
		if (p[index] == '"' || p[index] == '\'')
		{
			if (!flag || p[index] == flag)
			{
				if (!flag)
					flag = p[index];
				else if (p[index] == flag)
					flag = 0;
				tmp = ft_substr(p, 0, index);
				tmp1 = ft_substr(p, index + 1, ft_strlen(p));
				p = ft_strjoin(tmp, tmp1);
				continue ;
			}
		}
		index++;
	}
}
