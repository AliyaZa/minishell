/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:44:46 by mismene           #+#    #+#             */
/*   Updated: 2021/05/06 21:30:03 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_ins(t_command *command, t_parsed_data *parsed_data)
{
	if (fn_search(command->command, "echo"))
		fn_echo(command);
	else if (fn_search(command->command, "pwd") && *command->command)
		pwd(command);
	else if (fn_search(command->command, "env") && *command->command)
		print_env(parsed_data->env_data, command);
	else if (fn_search(command->command, "cd") && *command->command)
		fn_cd(command, parsed_data);
	else if (fn_search(command->command, "export") && *command->command)
		fn_export(parsed_data, command);
	else if (fn_search(command->command, "unset") && *command->command)
		fn_unset(parsed_data, command);
	else if (fn_search(command->command, "exit") && *command->command)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

void	fork_proccess(t_parsed_data *parsed_data, t_command *command)
{
	pid_t	child;
	pid_t	parent;
	pid_t	pid[2];

	child = pid[0];
	parent = pid[1];
	child = fork();
	signal(SIGINT, (void *)proc_signal_handler);
	if (child == 0)
		fn_fork(parsed_data, command);
	wait(&child);
}

void	router(t_parsed_data *parsed_data, t_command *command)
{
	if (command->command != NULL)
	{
		if (command->flags->pipe)
			fn_pipe(parsed_data, command);
		else if (is_build_in(command->command))
			build_ins(command, parsed_data);
		else if (fn_search(command->command, "minishell") && *command->command)
			level(parsed_data, command);
		else
			fork_proccess(parsed_data, command);
		if (command->fd[1] > 1)
			close(command->fd[1]);
		if (command->fd[0] > 0)
			close(command->fd[0]);
	}
	else
		return ;
}
