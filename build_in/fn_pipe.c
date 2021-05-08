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

static void	ft_success_fork(t_parsed_data *parsed_data, t_command *command,
	size_t i, int fd[command->pipes_quantity][2], char *path)
{
	if (i == 0)
	{
		// printf("first **** %i\n", i);
		// if (close(fd[i][0]) == - 1)
		// 	printf("1\n");
		dup2(fd[i][1], 1);
		if (close(fd[i][1]) == - 1)
			printf("2\n");
	}
	else if (i == (int)command->pipes_quantity)
	{
		// printf("last **** %i\n", i);
		dup2(fd[i - 1][0], 0);
		if (close(fd[i - 1][0]) == -1)
			printf("3\n");
		if (close(fd[i - 1][1]) == -1)
			printf("4\n");
		// path = "/bin/cat";
	}
	else
	{
		// printf("middle **** %i\n", i);
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		if (close(fd[i - 1][0]) == -1)
			printf("5\n");
		if (close(fd[i - 1][1]) == -1)
			printf("6\n");
		if (close(fd[i][0]) == -1)
			printf("7\n");
		if (close(fd[i][1]) == -1)
			printf("8\n");
		// path = "/bin/cat";
	}
	if (execve(path, command->pipes[i], fn_arr(parsed_data->env_data)) == -1)
		printf("error\n");
}

char		*determinne_command_path(t_command *command, size_t index)
{

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
	while (++i < command->pipes_quantity)
		pipe(fd[i]);
	i = 0;
	while (i < command->pipes_quantity + 1)
	{
		if ((path = determine_command_path(command)) != NULL)
		{
			pid = fork();
			if (pid == 0)
				ft_success_fork(parsed_data, command, i, fd, path);
			path = NULL;
		}
		j = i; //****
		i++;
	}
	// wait(&status);
	close(fd[j - 1][STDIN_FILENO]);
	close(fd[j - 1][STDOUT_FILENO]);
	j = -1;
	while (++j < (int)command->pipes_quantity + 1)
	{
		wait(&status);
		// close(fd[j - 1][STDIN_FILENO]);
		// close(fd[j - 1][STDOUT_FILENO]);
		// close(fd[i][0]);
		// close(fd[i][1]);
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
	// exit(0);
}
