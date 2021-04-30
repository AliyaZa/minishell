/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:17:43 by nhill             #+#    #+#             */
/*   Updated: 2021/04/29 19:56:58 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fn_errors(t_command *command, int error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->argument, 2);
	if (error == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd(": command not found\n", 1);
		exit (1);
	}
	else if (error == NO_FILE)
		ft_putstr_fd("No such file or directory\n", 1);
	else if (error == NOT_AN_EXECUTABLE_FILE)
	{
		ft_putstr_fd(":not an executable file.\n", 2);
		exit (1);
	}
	else if (error == SYNTAX_ERROR)
		ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	else if (error == IS_FILE)
		ft_putstr_fd(": not a directory\n", 2);
	else if (error == NOT_VALID_ID)
		ft_putstr_fd(": not a valid identifier\n", 2);
	else if (error == errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
	}
	command->flags->error = error;
	return (0);
}
