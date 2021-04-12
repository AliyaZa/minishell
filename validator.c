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

char	*get_key(char *string)
{
	int		index;
	char	*key;

	index = 0;
	key = ft_strdup(string);
	while (key[index])
	{
		if (key[index] == ' ' || key[index] == '"')
		{
			key[index] = 0;
			return (key);
		}
		index++;
	}
	return (NULL);
}

void	validator(char **string, t_env *env, t_command *command)
{
	char	*start;
	int		index;
	char	*save;
	char	flag;
	int		k;
	char	*value;
	char	*key;

	key = NULL;
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
			start = &start[index];
		}
		if (*start == '$' && (flag == 0 || flag == '"'))
		{
			*start++ = 0;
			key = get_key(start);
			value = get_value_by_key(env, key);
			save = ft_strdup(start + ft_strlen_c(start, ' '));
			*string = ft_strjoin(*string, value);
			*string = ft_strjoin(*string, save);
			free_str(&save);
			start = *string;
			start = &start[index + ft_strlen_c(start, ' ')];
		}
		else
		{
			start++;
			index++;
		}
	}
	if (flag)
	{
		fn_errors(command, SYNTAX_ERROR);
	}
}
