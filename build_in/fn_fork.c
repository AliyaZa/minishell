/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 21:56:32 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ret_er(char **places, int kol, struct stat buf)
{
	int		er;

	er = 0;
	if (places && places[kol])
	{
		if (S_ISDIR(buf.st_mode))
		{
			er = 21;
		}
		else if (!(buf.st_mode & S_IXUSR))
		{
			er = 13;
		}
	}
	return (er);
}

char		*for_norm(t_env *path, t_command *command, int *error)
{
	char		**places;
	int			kol;
	struct stat	buf;

	places = NULL;
	kol = 0;
	if (path)
		places = ft_split(path->value, ':');
	while (places && places[kol] && (stat(fn_strjoin3(places[kol],
					"/", command->command), &buf) != 0))
		kol++;
	if (ret_er(places, kol, buf) != 0)
	{
		*error = ret_er(places, kol, buf);
		return (NULL);
	}
	if (places && places[kol])
		return (fn_strjoin3(places[kol], "/", command->command));
	else
		return (ft_strdup(command->command));
}

char		*fn_path(t_parsed_data *parsed_data,
				t_command *command, int *error)
{
	t_env		*path;
	char		*path_to;

	path_to = NULL;
	path = fn_get_el(parsed_data, "PATH");
	if (command->flags->is_bin != 1)
	{
		path_to = for_norm(path, command, error);
	}
	else
		path_to = ft_strdup(command->command);
	return (path_to);
}

int			fn_redir(t_parsed_data *parsed_data, t_command *command)
{
	char	*path_to;
	int		error;
	int		save1;
	int		save0;

	save1 = dup(1);
	error = 0;
	save0 = dup(0);
	path_to = NULL;
	dup2(command->fd[1], 1);
	dup2(command->fd[0], 0);
	path_to = fn_path(parsed_data, command, &error);
	if (error == 0)
	{
		execve(path_to, command->splitted, fn_arr(parsed_data->env_data));
		dup2(save1, 1);
		dup2(save0, 0);
		return (0);
	}
	else
		return (error);
	return (COMMAND_NOT_FOUND);
}

void		fn_fork(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = fn_redir(parsed_data, command);
	if (error != 0)
	{
		if (error == COMMAND_NOT_FOUND)
			fn_errors(command, COMMAND_NOT_FOUND);
		else
			fn_errors(command, NOT_AN_EXECUTABLE_FILE);
	}
	exit(0);
}
