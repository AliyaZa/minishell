/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 17:30:35 by mismene          ###   ########.fr       */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser allocate memory, free it after usage
int		main(int argc, char **argv, char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	env_data = parse_env(env);
	parsed_data = parser();
	if (fn_search(parsed_data->command, "echo"))
	{
		fn_echo(parsed_data->rest_string);
	}
	printf("first argument - %s\n argc - %d\n", argv[0], argc);
	return (0);
}
