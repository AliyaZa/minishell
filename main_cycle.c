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

void	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;

	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	parsed_data->history = (char **)malloc(sizeof(char *) * 500);
	if (!parsed_data->history)
		return ;
	parsed_data->env_data = parse_env(env);
	while (1)
	{
		initialize_structure(parsed_data);
		write(1, "minishell> ", 11);
		fn_termcap(&parsed_data);
		write(1, parsed_data->raw_string, ft_strlen(parsed_data->raw_string));
		// parser(&parsed_data);
		// save_history(&parsed_data);
		router(parsed_data);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
	}
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
}
