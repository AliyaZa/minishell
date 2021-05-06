/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:10:44 by nhill             #+#    #+#             */
/*   Updated: 2021/05/04 18:16:51 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_success_fork(t_parsed_data *parsed_data, t_command *command,
	int i, int fd[command->pipes_quantity][2], char *path)
{
	int j;

	if (i == 0)
	{
		i < (int)command->pipes_quantity ? dup2(fd[i][1], 1) : 0;
		j = -1;
		while (++j < (sizeof(command->pipes) / sizeof(command->pipes[0])) - 1)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
	}
	else if (i < ((int)command->pipes_quantity - 1))
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		j = -1;
		while (++j < (int)command->pipes_quantity - 1)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
	}
	else
	{
		dup2(fd[i - 1][0], 0);
		j = -1;
		while (++j < (sizeof(command->pipes) / sizeof(command->pipes[0])) - 1)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
	}
	command->fd[1] != 1 ? dup2(command->fd[1], fd[i][0]) : 0;
	command->fd[0] != 1 ? dup2(command->fd[0], 1) : 0;
	execve(path, command->splitted, fn_arr(parsed_data->env_data));
}

int			fn_make_pipe(t_parsed_data *parsed_data, t_command *command)
{
	int		i;
	int		fd[command->pipes_quantity][2];
	char	*path;
	int		error;
	int		j;

	i = 0;
	while (i++ < (int)command->pipes_quantity)
		pipe(fd[i]);
	i = 0;
	while (i < (int)command->pipes_quantity)
	{
		if ((path = fn_path(parsed_data, command, &error)) != NULL)
		{
			fork() == 0 ? ft_success_fork(parsed_data,
				command, i, fd, path) : 0;
			path = NULL;
		}
		i++;
	}
	j = -1;
	while (++j < (int)command->pipes_quantity - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
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
	exit(0);
}
