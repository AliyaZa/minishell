/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:49 by mismene           #+#    #+#             */
/*   Updated: 2021/04/08 16:12:10 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_command		**command;
	size_t			flag;
	size_t			index;

	flag = 0;
	index = 0;
	command = (t_command **)(malloc(sizeof(t_command)))
	parsed_data = initialize_parsed_data(env);
	while (1)
	{
		command[index] = initialize_command();
		reset_(&command[index], flag);
		write(1, "minishell> ", 11);
		tputs(save_cursor, 1, ft_putchar);
		fn_termcap(&command[index], parsed_data->history);
		parser(command);
		save_history(&parsed_data, command[index]->raw_string);
		router(parsed_data, command[index]);
		free_str(&command[index]->raw_string);
		free_str(&command[index]->command);
		flag = 1;
	}
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
}
