/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:10:44 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 21:32:49 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_success_fork(t_command *command,
	size_t i, int fd[command->pipes_quantity][2])
{
	if (i == 0)
	{
		dup2(fd[i][1], 1);
		close(fd[i][1]);
	}
	else if (i == command->pipes_quantity)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	else
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

int			fn_make_pipe(t_parsed_data *parsed_data, t_command *command)
{
	size_t	i;
	int		fd[command->pipes_quantity][2];
	char	*path;
	int		error;
	int		j;
	int		status;
	int		pid;

	i = -1;
	error = 0;
	while (++i < command->pipes_quantity)
		pipe(fd[i]);
	i = 0;
	while (i < command->pipes_quantity + 1)
	{
		if ((path = determine_command_path(command, parsed_data, i)) != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				ft_success_fork(command, i, fd);
				execve(path, command->pipes[i], fn_arr(parsed_data->env_data));
			}
			path = NULL;
		}
		j = i;
		i++;
	}
	close(fd[j - 1][STDIN_FILENO]);
	close(fd[j - 1][STDOUT_FILENO]);
	j = -1;
	while (++j < (int)command->pipes_quantity + 1)
	{
		wait(&status);
	}
	return (error);
}

void		fn_pipe(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = 0;
	error = fn_make_pipe(parsed_data, command);
	if (error != 0)
		fn_errors(command, error);
}
