/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/05/04 18:00:59 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_lst(t_env *env)
{
	int		count;

	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

char	**fn_arr(t_env *env)
{
	int		kol;
	char	**res;
	int		i;

	kol = ft_count_lst(env);
	res = (char **)malloc(sizeof(char *) * (kol + 1));
	ft_bzero(res, sizeof(char *) * (kol + 1));
	i = 0;
	while (env)
	{
		if (env->equal == NULL)
			res[i++] = fn_strjoin3(env->key, "=", env->value);
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}

char	*fn_path(t_parsed_data *parsed_data, t_command *command, int *error)
{
	t_env	*path;
	char	**places;
	char	*path_to;
	int		kol;
	struct stat	buf;

	places = NULL;
	path_to = NULL;
	kol = 0;
	path = fn_get_el(parsed_data, "PATH");
	if (command->flags->is_bin != 1)
	{
		if (path)
			places = ft_split(path->value, ':');
		while (places && places[kol] && (stat(fn_strjoin3(places[kol],
						"/", command->command), &buf) != 0))
			kol++;
		if (places && places[kol])
		{
			if (S_ISDIR(buf.st_mode))
			{
				*error = 21; // its a directory
				return (NULL);
			}
			else if (!(buf.st_mode & S_IXUSR))
			{
				*error = 13;// its permission denied
				return(NULL);
			}
		}
		if (places && places[kol])
			path_to = fn_strjoin3(places[kol], "/", command->command);
		else
			path_to = ft_strdup(command->command);
	}
	else
		path_to = ft_strdup(command->command);
	return (path_to);
}

int	fn_redir(t_parsed_data *parsed_data, t_command *command)
{
	char	*path_to;
	int		error;
//	t_env	*mini;
//	int		level;


	int save1 = dup(1);
	int save0 = dup(0);
	error = 0;
	path_to = NULL;
	if (command->fd[1] > 1)
		dup2(command->fd[1], 1);
	if (command->fd[0] > 0)
		dup2(command->fd[0], 0);
	//free(command->splitted[0]);
	//command->splitted[0] = NULL;
	// command->splitted[0] = ft_strdup(command->argument);
	if (command->splitted[2] != NULL)
	{
		free(command->splitted[2]);
		command->splitted[2] = NULL;
	}
	for (int i = 0; i < 4; i++)
		printf("%s\n",command->splitted[i]);
	if (fn_path(parsed_data, command, &error))
	{
		execve(fn_path(parsed_data, command, &error), command->splitted, fn_arr(parsed_data->env_data));
		if (command->fd[1] > 1)
			dup2(save1, 1);
		if (command->fd[0] > 0)
			dup2(save0, 0);
		return (0);
	}
//	if (command->fd[1] > 1)
			dup2(save1, 1/*, save1*/);
//		if (command->fd[0] > 0)
			dup2(save0, 0/*, save0*/);
	//dup2(command->fd[0], command->fd[1]);
	return (COMMAND_NOT_FOUND);
}

void	fn_fork(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = 0;
	//if (!command->flags->is_bin)
		error = fn_redir(parsed_data, command);
/*	else
	{
		dup2(command->fd[1], 1);
		if ((execve(command->command, command->splitted, fn_arr(parsed_data->env_data)) == 0))
		{
			dup2(1, command->fd[1]);
			error = 0;
		}
	}*/
	if (error != 0)
	{
		if (error == COMMAND_NOT_FOUND)
			fn_errors(command, COMMAND_NOT_FOUND);
		else
			fn_errors(command, NOT_AN_EXECUTABLE_FILE);
	}
	exit (0);
}
