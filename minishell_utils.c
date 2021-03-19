/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:21:10 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 11:01:07 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
