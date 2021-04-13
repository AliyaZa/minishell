/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:21:10 by mismene           #+#    #+#             */
/*   Updated: 2021/04/07 17:52:14 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fn_search(char *s1, char *s2)
{
	if (s1 && s2)
	{
		if (ft_strcmp(s1, s2) == 0)
			return (1);
	}
	return (0);
}

char	*get_value_by_key(t_env *env_data, char *key)
{
	while (env_data->next != NULL)
	{
		if (!ft_strncmp(key, env_data->key, ft_strlen(key)))
		{
			return (env_data->value);
		}
		env_data = env_data->next;
	}
	return (NULL);
}

void	string_tolower(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != 0)
	{
		string[i] = ft_tolower(string[i]);
		i++;
	}
}

char	*ft_strnew(unsigned int size)
{
	char	*string;

	string = malloc((sizeof(char) * size) + 1);
	if (string == NULL)
		return (NULL);
	string[size] = 0;
	return (string);
}

size_t	command_len(const char *command)
{
	size_t	i;

	i = 0;
	while (command[i] != ' ')
	{
		i++;
	}
	return (i);
}
