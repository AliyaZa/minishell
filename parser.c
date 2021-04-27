/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/04/12 18:58:38 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*determine_argument(t_command *command)
{
	char	*arg;
	size_t	index;

	arg = command->rest_string;
	index = 0;
	if (command->option)
	{
		arg = ft_strchr(command->rest_string, command->option);
		arg++;
	}
	while ((!(ft_isprint(*arg)) && ft_strlen(arg)) || (*arg == ' '))
		arg++;
	while (arg[index] && arg[index] != '\"' && arg[index] != '\n')
	{
		index++;
	}
	return (arg);
}

void	determine_rest_string(t_command **command, size_t index)
{
	size_t	strlen;

	strlen = ft_strlen((*command)->rest_string);
	while ((*command)->option == 'n' && index > 0)
	{
		(*command)->rest_string++;
		index--;
	}
	while (!(ft_isprint(*(*command)->rest_string))
		&& (*(*command)->rest_string != ' ') && strlen)
	{
		if (*(*command)->rest_string == (*command)->option)
			(*command)->rest_string++;
		(*command)->rest_string++;
	}
}

void	determine_options(t_command **command)
{
	char	option;
	size_t	index;

	index = 0;
	option = 0;
	while ((*command)->rest_string[index])
	{
		if ((*command)->rest_string[index] == '-')
		{
			if (ft_isalpha((*command)->rest_string[index + 1]))
			{
				(*command)->option = (*command)->rest_string[index + 1];
				break ;
			}
		}
		index++;
	}
	determine_rest_string(command, index);
}

char	*determine_command(t_command **command)
{
	int		i;
	char	*p;
	char	*command_p;

	p = (*command)->raw_string;
	i = 0;
	while (*p == ' ')
	{
		p++;
	}
	command_p = p;
	while (ft_isprint(*p) && *p != ' ')
	{
		p++;
		i++;
	}
	(*command)->command = (char *)malloc((sizeof(char) * i) + 1);
	ft_strlcpy((*command)->command, command_p, (size_t)(i + 1));
	string_tolower((*command)->command);
	return (p);
}

void	parser(t_command **command, t_env *env)
{
	char	*tmp;

	if (!ft_strlen((*command)->raw_string) && (*command)->queue)
		(*command)->raw_string = ft_strdup((*command)->queue);
	if (!ft_strncmp_end((*command)->raw_string, "\x03", 1) || (ft_strlen(
		(*command)->raw_string) == 0 && ft_strlen((*command)->queue) == 0))
		return ;
	if (!ft_strncmp((*command)->raw_string, "\n", 1))
		return ;
	replace_symbol(&(*command)->raw_string, '\n', '\0');
	semicolon(command);
	determine_command_struct(command, env);
	(*command)->splited = ft_split((*command)->raw_string, ' ');
	if ((*command)->flags->is_bin)
	{
		tmp = ft_strdup((*command)->command);
		(*command)->argument = ft_strdup((*command)->splited[0]);
		if (!(is_current_folder((*command)->command)))
			(*command)->splited[0] =
			ft_strdup((ft_strrchr((*command)->splited[0], '/') + 1));
		(*command)->command = ft_strdup((ft_strrchr(tmp, '/') + 1));
	}
}
