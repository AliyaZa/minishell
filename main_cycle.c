/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:49 by mismene           #+#    #+#             */
/*   Updated: 2021/03/23 16:07:58 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	parsed_data->user_commands = (char **)malloc(sizeof(char *) * 500);
	if (!parsed_data->user_commands)
		return ;
	while (1)
	{
		env_data = parse_env(env_data);
		parser(&parsed_data);
		router(parsed_data, env_data);
		save_history(&parsed_data);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
	}
}
