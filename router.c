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

void	print_history(t_parsed_data *parsed_data)
{
	for (int i = 499; i; i--)
	{
		printf("%s %d\n", parsed_data->history[i], i);
	}
}

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
	else if (fn_search(parsed_data->command, "hist") && *parsed_data->command)
		print_history(parsed_data);
	else
	{
		write(1, "command not found\n", 18);
	}
}
