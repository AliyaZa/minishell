/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:49 by mismene           #+#    #+#             */
/*   Updated: 2021/03/24 18:46:54 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_structure(t_parsed_data *parsed_data)
{
	parsed_data->raw_string = NULL;
	parsed_data->command = NULL;
	parsed_data->option = 0;
	parsed_data->argument = NULL;
	parsed_data->history = NULL;
}

void	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	parsed_data->history = (char **)malloc(sizeof(char *) * 500);
	if (!parsed_data->history)
		return ;
	initialize_structure(parsed_data);
	while (1)
	{
		write(1, "minishell> ", 11);
		env_data = parse_env(env);
		parser(&parsed_data);
		router(parsed_data, env_data);
		// save_history(&parsed_data);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
		parsed_data->option = 0;
	}
}
