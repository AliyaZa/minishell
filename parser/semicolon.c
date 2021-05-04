/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:41:34 by mismene           #+#    #+#             */
/*   Updated: 2021/04/27 14:41:36 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	semicolon(t_command *command)
{
	char	*string;
	int		index;
	int		counter;

	string = command->raw_string;
	index = 0;
	counter = 0;
	while (string[index])
	{
		if (string[index] == ';')
		{
			counter++;
			string[index] = 0;
			command->queue = ft_strdup(&string[index + 1]);
			break ;
		}
		index++;
	}
	if (!counter)
	{
		command->queue = NULL;
	}
}
