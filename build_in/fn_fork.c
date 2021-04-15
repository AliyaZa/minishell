/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/04/15 16:18:17 by nhill            ###   ########.fr       */
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

static char	**fn_array(t_env *env)
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

static int	fn_path(t_parsed_data *parsed_data, t_command *command)
{
	t_env	*path;
	char	**places;
	int		kol;
	char	*path_to;

	kol = 0;
	places = NULL;
	path_to = NULL;
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
	if ((execve(path_to, command->splited, fn_array(parsed_data->env_data)) == 0))
		return (0);
	return (COMMAND_NOT_FOUND);
}

void	fn_fork(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = fn_path(parsed_data, command);
	if (error != 0)
	{
		if (error == COMMAND_NOT_FOUND)
			fn_errors(command, COMMAND_NOT_FOUND);
		else
			fn_errors(command, NOT_AN_EXECUTABLE_FILE);
	}
	exit (0);
}
