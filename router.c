/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:44:46 by mismene           #+#    #+#             */
/*   Updated: 2021/04/06 17:34:34 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	router(t_parsed_data *parsed_data)
{
	if (fn_search("echo", parsed_data->command))
	{
		fn_echo(parsed_data);
	}
	else if (fn_search(parsed_data->command, "pwd") && *parsed_data->command)
	{
		pwd(parsed_data->env_data);
	}
	else if (fn_search(parsed_data->command, "env") && *parsed_data->command)
	{
		print_env(parsed_data->env_data);
	}
	else if (fn_search(parsed_data->command, "cd") && *parsed_data->command)
	{
		fn_cd(parsed_data);
	}
	else
	{
		write(1, "command not found\n", 18);
	}
}
