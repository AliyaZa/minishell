/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/05/03 17:47:05 by nhill            ###   ########.fr       */
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

char	*fn_path(t_parsed_data *parsed_data, t_command *command)
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
				return(errno = 21); // its a directory
			else if (!(buf.st_mode & S_IXUSR))
				return(errno = 13);// its permission denied
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

static void	level(t_parsed_data *parsed_data, t_command *command)
{
	t_env	*mini;
	int		level;

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
}

int	fn_path(t_parsed_data *parsed_data, t_command *command)
{
	char	*path_to;
//	t_env	*mini;
//	int		level;


	int save1 = dup(1);
	int save0 = dup(0);
	path_to = NULL;
	if (command->fd[1] > 1)
		dup2(command->fd[1], 1);
	if (command->fd[0] > 0)
		dup2(command->fd[0], 0);
	level(parsed_data, command);
	// if (fn_search(command->command, "minishell"))
	// {
	// 	mini = fn_get_el(parsed_data, "SHLVL");
	// 	if (check_digit(mini->value) == 0)
	// 		level = 0;
	// 	else
	// 		level = ft_atoi(mini->value);
	// 	if ((level < 999))
	// 	{
	// 		if (!(mini->value = ft_itoa(level + 1)))
	// 			return(errno);
	// 	}
	// 	else if (level == 999)
	// 		mini->value = "";
	// }
	free(command->splitted[0]);
	command->splitted[0] = NULL;
	command->splitted[0] = ft_strdup(command->argument);
	command->splitted[2] = NULL;
	if ((execve(fn_path(parsed_data, command), command->splitted, fn_arr(parsed_data->env_data)) == 0))
	{
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
		error = fn_path(parsed_data, command);
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
