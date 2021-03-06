/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/04/29 18:43:15 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	determine_command_struct(t_command *command, t_env *env)
{
	command->rest_string = determine_command(command);
	if (validate_command(&command->command))
		fn_errors(command, SYNTAX_ERROR);
	command->flags->is_bin = is_command_bin(command);
	determine_options(command);
	command->argument = determine_argument(command);
	validator(&command->argument, env, command);
	if (!is_build_in(command->command))
		command->raw_string = validate_raw_string(command->raw_string);
}

size_t		three_dim_size(char ***array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void		parser(t_command *command, t_env *env)
{
	char	*tmp;

	if (!ft_strlen(command->raw_string) && command->queue)
		command->raw_string = ft_strdup(command->queue);
	if (!ft_strncmp(command->raw_string, "\n", 1))
		return ;
	replace_symbol(&command->raw_string, '\n', '\0');
	semicolon(command);
	determine_command_struct(command, env);
	command->splitted = get_splitted(command->raw_string);
	if ((command->pipes = get_pipes(command)))
		command->pipes_quantity = three_dim_size(command->pipes) - 1;
	replace_symbol_array(&command->splitted, -1, ' ');
	delete_quotes(&command->splitted);
	if (command->flags->is_bin)
	{
		tmp = ft_strdup(command->command);
		command->argument = ft_strdup(command->splitted[0]);
		if (!(is_current_folder(command->command)))
			command->splitted[0] =
			ft_strdup((ft_strrchr(command->splitted[0], '/') + 1));
		command->command = ft_strdup((ft_strrchr(tmp, '/') + 1));
	}
}
