/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/04/27 20:34:05 by nhill            ###   ########.fr       */
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

static char	**fn_arr(t_env *env)
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

static int	check_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	fn_path(t_parsed_data *parsed_data, t_command *command)
{
	t_env	*path;
	char	**places;
	int		kol;
	char	*path_to;
	t_env	*mini;
	int		level;

	kol = 0;
	places = NULL;
	path_to = NULL;
	//if (command->flags->is_bin != 1)
	path = fn_get_el(parsed_data, "PATH");
	if (path)
		places = ft_split(path->value, ':');
	while (places && places[kol] && (access(fn_strjoin3(places[kol],
					"/", command->command), F_OK) == -1))
		kol++;
	if ((places && places[kol] && access(fn_strjoin3(places[kol],
					"/", command->command), X_OK) == -1) || (!access
			(command->command, F_OK) && access(command->command, X_OK) == -1))
		return (NOT_AN_EXECUTABLE_FILE);
	if (places && places[kol])
		path_to = fn_strjoin3(places[kol], "/", command->command);
	else
		path_to = ft_strdup(command->argument);
	if (command->fd[1] > 1)
		dup2(command->fd[1], 1);
	if (fn_search(command->command, "minishell"))
	{
		mini = fn_get_el(parsed_data, "SHLVL");
		if (check_digit(mini->value) == 0)
			level = 0;
		else
			level = ft_atoi(mini->value);
		if ((level < 999))
		{
			if (!(mini->value = ft_itoa(level + 1)))
				return(errno);
		}
		else if (level == 999)
			mini->value = "";
	}
	if ((execve(path_to, command->splited, fn_arr(parsed_data->env_data)) == 0))
	{
		dup2(1, command->fd[1]);
		return (0);
	}
	return (COMMAND_NOT_FOUND);
}

void	fn_fork(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = 0;
	//if (!command->flags->is_bin)
		error = fn_path(parsed_data, command);
/*	else
	{
		dup2(command->fd[1], 1);
		if ((execve(command->command, command->splited, fn_arr(parsed_data->env_data)) == 0))
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
