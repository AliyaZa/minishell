/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:19:54 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 20:37:59 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		fn_redir_helper(t_command *command,
				t_parsed_data *parsed_data, int *error)
{
	if (command->fd[1] > 1)
		dup2(command->fd[1], 1);
	if (command->fd[0] > 0)
		dup2(command->fd[0], 0);
	fn_path(parsed_data, command, error);
}

char		*determine_command_path(t_command *command,
				t_parsed_data *parsed_data, size_t j)
{
	char	**pathes;
	size_t	index;
	char	*path;

	pathes = ft_split(get_value_by_key(parsed_data->env_data, "PATH"), ':');
	index = 0;
	while (pathes[index])
	{
		path = ft_strjoin(pathes[index], "/");
		if (fopen((path = ft_strjoin(path, command->pipes[j][0])), "r"))
			return (path);
		index++;
	}
	return (NULL);
}
