/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:22 by mismene           #+#    #+#             */
/*   Updated: 2021/04/27 14:42:23 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*initialize_command(void)
{
	t_command	*command;
	t_flags		*flags;

	flags = malloc(sizeof(flags));
	command = (t_command *)malloc(sizeof(t_command));
	command->raw_string = ft_strnew(0);
	command->command = NULL;
	command->option = 0;
	command->argument = NULL;
	command->rest_string = 0;
	command->queue = NULL;
	command->fd[0] = 0;
	command->fd[1] = 1;
	command->flags = flags;
	command->flags->is_bin = 0;
	command->flags->rev_redirect = 0;
	command->flags->error = 0;
	command->flags->pipe = 0;
	return (command);
}

t_parsed_data	*initialize_parsed_data(char **env)
{
	t_parsed_data	*parsed_data;

	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	parsed_data->history = (char **)ft_calloc(500, sizeof(char *));
	parsed_data->env_data = parse_env(env);
	return (parsed_data);
}

void			reset_(t_command **command, size_t flag)
{
	if (flag)
	{
		free_str(&(*command)->raw_string);
		free_str(&(*command)->command);
		free_str(&(*command)->argument);
		(*command)->flags->is_bin = 0;
		(*command)->flags->error = 0;
		(*command)->fd[0] = 0;
		(*command)->fd[1] = 1;
		(*command)->raw_string = ft_strnew(0);
		(*command)->option = 0;
		(*command)->rest_string = 0;
	}
}
