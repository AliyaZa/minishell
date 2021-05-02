/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:10:44 by nhill             #+#    #+#             */
/*   Updated: 2021/05/02 20:13:03 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		kol_pipe(char **arr)
{
	int		i;
	int		j;
	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][j])
		{
			j++;
		}
		i++;
	}
	return(i);
	//sizeof(arr)/sizeof(arr[0]);
}
//форк перепиши

static void	ft_success_fork(t_parsed_data *parsed_data, t_command *command,
	int i, int **fd)
{
	int j;
	char *path;

	if (i == 0)
	{
		i < (sizeof(command->pipes)/sizeof(command->pipes[0])) ? dup2(fd[i][1], 1) : 0;
//		ft_close_descript(all->count_com, fd, -1);
		j = -1;
		while (++j < (sizeof(command->pipes)/sizeof(command->pipes[0])) - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
	}
	else if (i < ((sizeof(command->pipes)/sizeof(command->pipes[0])) - 1))
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
//		ft_close_descript(all->count_com, fd, -1);
		j = -1;
		while (++j < (sizeof(command->pipes)/sizeof(command->pipes[0])) - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
	}
	else
	{
		dup2(fd[i - 1][0], 0);
//		ft_close_descript(all->count_com, fd, -1);
		j = -1;
		while (++j < (sizeof(command->pipes)/sizeof(command->pipes[0])) - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
	}
	command->fd[1] != 1 ? dup2(command->fd[1], fd[i][0]) : 0;
	command->fd[0] != 1 ? dup2(command->fd[0] , 1) : 0;
	execve(path, command->splitted, fn_arr(parsed_data->env_data));
}

// kol_pipe(command->pipes);
int		fn_pipe(t_parsed_data *parsed_data ,t_command *command, int kol)
{
	int		i;
	int		fd[kol][2];

	i = 0;
	while (i++ < kol)
		pipe(fd[i]);
	i = 0;
	while (command->pipes)
	{
		router(parsed_data, command);
	}
}
