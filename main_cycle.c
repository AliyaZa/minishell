/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:49 by mismene           #+#    #+#             */
/*   Updated: 2021/04/13 20:35:17 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_command		*command;
	size_t			flag;

	flag = 0;
	command = initialize_command();
	parsed_data = initialize_parsed_data(env);
	while (1)
	{
		reset_(command, flag);
		if (!command->queue)
		{
			ft_putstr_fd("minishell> ", 1);
			tputs(save_cursor, 1, ft_putchar);
			fn_termcap(command, parsed_data->history);
			if (command->raw_string[0] != '\n')
				save_history(parsed_data, command->raw_string);
		}
		parser(command, parsed_data->env_data);
		if (!(command->flags->error))
			router(parsed_data, command);
		flag = 1;
	}
	free_memory(parsed_data, command);
	return (0);
}
