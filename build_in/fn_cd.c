/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:35:24 by nhill             #+#    #+#             */
/*   Updated: 2021/04/15 18:00:09 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*fn_get_el(t_parsed_data *parsed_data, char *key)
{
	t_env	*tmp;

	tmp = parsed_data->env_data;
	while (tmp && !(fn_search(tmp->key, key)))
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

static char	*fn_new_path(t_env *home, t_command *command)
{
	char	*path;
	char	*new_path;

	path = NULL;
	new_path = NULL;
	path = getcwd(path, PATH_MAX);
	if (command->argument && !(fn_search(command->argument, "~")))
		new_path = fn_strjoin3(path, "/", command->argument);
	else
		new_path = ft_strdup(home->value);
	free(path);
	path = NULL;
	return (new_path);
}

static char	*fn_get_path(t_parsed_data *parsed_data, t_command *command)
{
	char	*new_path;
	t_env	*home;
	t_env	*tmp;

	new_path = NULL;
	home = NULL;
	tmp = NULL;
	home = fn_get_el(parsed_data, "HOME");
	if (!home && !command->command)
		return (NULL);
	else if (command->argument && command->argument[0] == '/')
		new_path = ft_strdup(command->argument);
	else if (fn_search(command->argument, "-"))
	{
		if (!(fn_get_el(parsed_data, "OLDPWD")))
			return (NULL);
		else
		{
			tmp = fn_get_el(parsed_data, "OLDPWD");
			new_path = ft_strdup(tmp->value);
		}
	}
	else
		new_path = fn_new_path(home, command);
	return (new_path);
}

static void	fn_change_cd(t_parsed_data *parsed_data, t_command *command,
char *path, char *env_key)
{
	t_env	*lst_name;
	char	*tmp;

	lst_name = NULL;
	tmp = NULL;
	lst_name = fn_get_el(parsed_data, env_key);
	if (lst_name)
	{
		free(lst_name->value);
		lst_name->value = NULL;
		lst_name->value = ft_strdup(path);
	}
	else
	{
		tmp = ft_strjoin(env_key, "=");
		fn_set_env(parsed_data, command, tmp, 0);
	}
}

void	fn_cd(t_command *command, t_parsed_data *parsed_data)
{
	char	*path;
	char	*new_path;

	path = NULL;
	new_path = NULL;
	new_path = fn_get_path(parsed_data, command);
	if (new_path)
	{
		if (fn_check(new_path, command))
		{
			path = getcwd(path, PATH_MAX);
			if (!(chdir(new_path)))
			{
				fn_change_cd(parsed_data, command, path, "OLDPWD");
				free(path);
				path = NULL;
				path = getcwd(path, PATH_MAX);
				fn_change_cd(parsed_data, command, path, "PWD");
			}
			free_str(&path);
		}
		free_str(&new_path);
	}
}
