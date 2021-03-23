/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:44:46 by mismene           #+#    #+#             */
/*   Updated: 2021/03/23 18:47:25 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	router(t_parsed_data *parsed_data, t_env *env_data)
{
	if (fn_search("echo", parsed_data->command))
	{
		printf("command = %s\necho = %s\n",parsed_data->command, parsed_data->rest_string);
		fn_echo(parsed_data->rest_string);
	}
	else if (fn_search(parsed_data->command, "pwd") && *parsed_data->command)
	{
		printf("%s\n", get_value_by_key(env_data, "PWD"));
	}
	else if (fn_search(parsed_data->command, "env") && *parsed_data->command)
	{
		print_env(env_data);
	}
	else if (fn_search(parsed_data->command, "cd"))
	{
		chdir("..");
	}
}
