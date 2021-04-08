/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:49 by mismene           #+#    #+#             */
/*   Updated: 2021/04/05 18:58:52 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_(t_command **command, size_t flag)
{
	if (flag)
	{
		(*command)->raw_string = ft_strnew(0);
		(*command)->option = 0;
		(*command)->argument = 0;
		(*command)->rest_string = 0;
	}
}

int		main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_command		*command;
	size_t			flag;

	flag = 0;
	command = initialize_command();
	parsed_data = initialize_parsed_data();
	while (1)
	{
		reset_(&command, flag);
		write(1, "minishell> ", 11);
		tputs(save_cursor, 1, ft_putchar);
		fn_termcap(&command);
		parser(&command);
		save_history(&parsed_data);
		// router(parsed_data);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
		flag = 1;
	}
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
}
