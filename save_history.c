/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:48:08 by mismene           #+#    #+#             */
/*   Updated: 2021/03/22 19:53:11 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_history(t_parsed_data **parsed_data)
{
	int				i;
	
	i = 498;
	while (i >= 0)
	{
		if ((*parsed_data)->user_commands[i])
		{
			(*parsed_data)->user_commands[i + 1] = ft_strdup((*parsed_data)->user_commands[i]);
		}
		i--;
	}
	(*parsed_data)->user_commands[10] = ft_strdup("hello world");
	(*parsed_data)->user_commands[0] = ft_strdup((*parsed_data)->raw_string);
	for (i = 499; i >=0; i--)
	{
		if ((*parsed_data)->user_commands[i])
		{
			printf("%s\n", (*parsed_data)->user_commands[i]);
		}
		else
			printf("%d\n", i);
	}
}
