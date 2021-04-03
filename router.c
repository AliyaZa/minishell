/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:44:46 by mismene           #+#    #+#             */
/*   Updated: 2021/03/24 18:39:30 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	router(t_parsed_data *parsed_data, t_env *env_data)
{
	if (fn_search("echo", parsed_data->command))
	{
		fn_echo(parsed_data);
	}
	else if (fn_search(parsed_data->command, "pwd") && *parsed_data->command)
	{
		pwd(env_data);
	}
	else if (fn_search(parsed_data->command, "env") && *parsed_data->command)
	{
		print_env(env_data);
	}
	else
	{
		write(1, "command not found\n", 18);
	}
}
