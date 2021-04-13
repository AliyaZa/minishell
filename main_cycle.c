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

void	redirect(t_command *command)
{
	int		fd;
	int		index;

	index = 0;
	fd = -1;
	while (command->splited[index])
	{
		if (!ft_strncmp(command->splited[index], ">>", 2))
		{
			fd = open(command->splited[index + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				ft_putstr_fd("file can't be created\n", 1);
			write(fd, command->splited[index - 1], ft_strlen(command->splited[index - 1]));
			close(fd);
			break ;
		}
		if (!ft_strncmp(command->splited[index], ">", 1))
		{
			fd = open(command->splited[index + 1], O_RDWR | O_CREAT, 0644);
			if (fd == -1)
				ft_putstr_fd("file can't be created\n", 1);
			write(fd, command->splited[index - 1], ft_strlen(command->splited[index - 1]));
			close(fd);
			break ;
		}
		index++;
	}
}

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
		reset_(&command, flag);
		if (!command->queue)
		{
			write(1, "minishell> ", 11);
			tputs(save_cursor, 1, ft_putchar);
			fn_termcap(&command, parsed_data->history);
			save_history(&parsed_data, command->raw_string);
		}
		parser(&command, parsed_data->env_data);
		redirect(command);

		router(parsed_data, command);
		flag = 1;
	}
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
	free(command);
}
