/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 20:39:32 by nhill            ###   ########.fr       */
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

char		*fn_path(t_parsed_data *parsed_data, t_command *command, int *error)
{
	t_env		*path;
	char		**places;
	char		*path_to;
	int			kol;
	struct stat	buf;

	places = NULL;
	path_to = NULL;
	path = fn_get_el(parsed_data, "PATH");
	if (command->flags->is_bin != 1 && (kol = 0))
	{
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
			path_to = fn_strjoin3(places[kol], "/", command->command);
		else
			path_to = ft_strdup(command->command);
	}
	else
		path_to = ft_strdup(command->command);
	return (path_to);
}

int			fn_redir(t_parsed_data *parsed_data, t_command *command)
{
	char	*path_to;
	int		error;

	int save1 = dup(1);
	int save0 = dup(0);
	error = 0;
	path_to = NULL;
	if (command->fd[1] > 1)
		dup2(command->fd[1], 1);
	if (command->fd[0] > 0)
		dup2(command->fd[0], 0);
	fn_path(parsed_data, command, &error);
	if (error == 0)
	{
		if (command->fd[1] > 1)
			dup2(save1, 1);
		if (command->fd[0] > 0)
			dup2(save0, 0);
		return (0);
	}
	else
		return(error);
	dup2(save1, 1);
	dup2(save0, 0);
	return (COMMAND_NOT_FOUND);
}

void		fn_fork(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = 0;
		error = fn_redir(parsed_data, command);
	if (error != 0)
	{
		if (error == COMMAND_NOT_FOUND)
			fn_errors(command, COMMAND_NOT_FOUND);
		else
			fn_errors(command, NOT_AN_EXECUTABLE_FILE);
	}
	exit (0);
}
