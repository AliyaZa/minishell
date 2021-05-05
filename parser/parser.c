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

void		validate_q(char *quote, char *p, size_t index)
{
	if (*quote == 0)
		*quote = p[index];
	else if (*quote == p[index])
		*quote = 0;
}

void		validate_pipe(char **raw_string)
{
	size_t	index;
	char	quote;
	char	*p;

	p = *raw_string;
	index = 0;
	quote = '\0';
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
			validate_q(&quote, p, index);
		else if (p[index] == '|' && quote)
			p[index] = -1;
		else if (p[index] == '\\')
			p[index + 1] = -1;
		index++;
	}
}

void		validate_spaces(char **string)
{
	char	*p;
	size_t	index;
	char	quote;

	quote = '\0';
	p = *string;
	index = 0;
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
			validate_q(&quote, p, quote);
		else if (p[index] == ' ' && quote)
			p[index] = -1;
	}
}

void		replace_symbol3(char ****array, char old, char new)
{
	char	***p;
	size_t	index;

	p = *array;
	index = 0;
	while (p[index])
	{
		replace_symbol_array(p, old, new);
		index++;
	}
}

char		***get_pipes(t_command *command)
{
	char	**matrix;
	char	***pipes;
	size_t	i;
	char	*p;

	i = 0;
	p = ft_strdup(command->raw_string);
	if (ft_strchr(command->raw_string, '|'))
		command->flags->pipe = 1;
	validate_pipe(&p);
	matrix = ft_split(p, '|');
	replace_symbol_array(&matrix, -1, '|');
	pipes = (char ***)malloc(sizeof(char **) * array_size(matrix));
	while (matrix[i])
	{
		validate_spaces(&matrix[i]);
		pipes[i] = ft_split(matrix[i], ' ');
		replace_symbol3(&pipes, -1, ' ');
		i++;
	}
	return (pipes);
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
	command->pipes = get_pipes(command);
	// print_array3(command->pipes);
	// command->pipes_quantity = array_size(command->pipes);
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
