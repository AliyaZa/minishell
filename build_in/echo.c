/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:59:28 by nhill             #+#    #+#             */
/*   Updated: 2021/04/21 19:16:27 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fn_echo(t_command *command)
{
	write(command->fd[1], command->argument, ft_strlen(command->argument));
	if (command->option != 'n')
	{
		write(command->fd[1], "\n", 1);
		return ;
	}
}
