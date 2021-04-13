/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:57:20 by nhill             #+#    #+#             */
/*   Updated: 2021/04/12 18:54:17 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fn_path(t_parsed_data *parsed_data, t_command *command)
{
	t_env	*path;
	char	**places;
	int		kol;

	kol = 0;
	places = NULL;
	path = fn_get_el(parsed_data, "PATH");
	if (path)
		places = ft_split(path->value, ':');
	while (places && places[kol] && (access(fn_strjoin3(places[kol],
					"/", command->argument), F_OK) == -1))
		kol++;
	if ((places && places[kol] && access(fn_strjoin3(places[kol],
					"/", command->argument), X_OK) == -1) || (!access
			(command->argument, F_OK) && access(command->argument, X_OK) == -1))
		return (0);
	return (COMMAND_NOT_FOUND);
}

void	fn_fork(t_parsed_data *parsed_data, t_command *command)
{
	int		error;

	error = fn_path(parsed_data, command);
	if (error != 0)
	{
//		execve(command->command, command->argument, parsed_data->env_data);
		if (error == COMMAND_NOT_FOUND)
			fn_errors(command, COMMAND_NOT_FOUND);
		else
			fn_errors(command, NOT_AN_EXECUTABLE_FILE);
	}
	exit (0);
}
