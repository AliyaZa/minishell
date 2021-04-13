/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:17:43 by nhill             #+#    #+#             */
/*   Updated: 2021/04/13 16:19:05 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fn_errors(t_command *command, int error)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(command->raw_string, 2);
	if (error == COMMAND_NOT_FOUND)
		write(2, ": command not found\n", 20);
	else if (error == NOT_AN_EXECUTABLE_FILE)
		ft_putstr_fd(": not an executable file\n", 2);
	else if (error == SYNTAX_ERROR)
	{
		ft_putstr_fd("syntax error: unexpected end of file", 2);
	}
	else if (errno)
		ft_putstr_fd(strerror(errno), 2);
	exit (1);
}
