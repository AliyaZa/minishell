/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:44:46 by mismene           #+#    #+#             */
/*   Updated: 2021/04/08 16:19:09 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	router(t_parsed_data *parsed_data, t_command *command)
{
	if (fn_search(command->command, "echo"))
	{
		fn_echo(command);
	}
	else if (fn_search(command->command, "pwd") && *command->command)
	{
		pwd(parsed_data->env_data);
	}
	else if (fn_search(command->command, "env") && *command->command)
	{
		print_env(parsed_data->env_data);
	}
	else if (fn_search(command->command, "cd") && *command->command)
	{
		fn_cd(command, parsed_data);
	}
	else
	{
		write(1, "command not found\n", 18);
	}
}
