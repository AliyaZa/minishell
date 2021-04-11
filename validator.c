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

char	*determine_rest_string(char *string)
{
	while (*string)
	{
		if (*string == ' ')
		{
			break ;
		}
		string++;
	}
	return (ft_strdup(string));
}

static char *determine_key(char *string)
{
	char	*key;
	int		index;

	index = 0;
	key = string;
	while (ft_isprint(string[index]))
	{
		if (string[index] == ' ' || string[index] == '\'' || string[index] == '"')
		{
			string[index] = 0;
			break ;
		}
		index++;
	}
	return (key);
}

void	validator(char **string, t_env *env)
{
	int		index;
	char	quot_type;
	char	*p;
	int		flag;
	char	*rest_string;
	char	*key;
	char	*value;

	key = NULL;
	p = *string;
	index = 0;
	quot_type = 0;
	flag = 0;
	(void)env->key;
	while (p[index])
	{
		if (p[index] == '"' || p[index] == '\'')
		{
			quot_type = p[index];
			*string += 1;
			p++;
		}
		if (p[index] == '$' && quot_type == '"')
		{
			p[index] = 0;
			p += index + 1;
			rest_string = ft_strdup(p);
			key = determine_key(&p[index]);
			value = get_value_by_key(env, key);
			rest_string = determine_rest_string(rest_string);
			*string = ft_strjoin(*string, value);
			*string = ft_strjoin2(*string, rest_string);
		}
		index++;
	}
}
