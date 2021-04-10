/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:44:46 by mismene           #+#    #+#             */
/*   Updated: 2021/04/09 19:31:42 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	router(t_parsed_data *parsed_data, t_command *command)
{
	pid_t	pid[2];
	pid_t	child;
	pid_t	parent;
	int		status;

	child = pid[0];
	parent = pid[1];
	if (fn_search(command->command, "echo"))
		fn_echo(command);
	else if (fn_search(command->command, "pwd") && *command->command)
		pwd(parsed_data->env_data);
	else if (fn_search(command->command, "env") && *command->command)
		print_env(parsed_data->env_data);
	else if (fn_search(command->command, "cd") && *command->command)
		fn_cd(command, parsed_data);
	else if (fn_search(command->command, "export") && *command->command)
		fn_export(parsed_data, command);
	else if (fn_search(command->command, "unset") && *command->command)
		fn_unset(parsed_data, command);
	else if (fn_search(command->command, "exit") && *command->command)
		exit(0);
	else
	{
		if (!command->command)
			return ;
		child = fork();
		if (child == 0)
			fn_fork(parsed_data, command);
		while ((parent = wait(&status)) > 0)
		;
	}
}
