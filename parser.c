/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/04/07 18:23:35 by nhill            ###   ########.fr       */
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
	while ((arg[index] != '\"' && arg[index] != '\n') && command->is_in_quotes)
	{
		index++;
	}
	if (command->is_in_quotes)
		arg[index] = 0;
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
	while (!(ft_isprint(*(*command)->rest_string)) && (*(*command)->rest_string != ' ') && strlen)
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

	p = (*command)->raw_string;
	i = 0;
	while (!(ft_isalpha(*p)))
	{
		p++;
	}
	while (ft_isalpha(*p))
	{
		p++;
		i++;
	}
	(*command)->command = (char *)malloc((sizeof(char) * i) + 1);
	ft_strlcpy((*command)->command, (*command)->raw_string, (size_t)(i + 1));
	string_tolower((*command)->command);
	return (p);
}

void	determine_struct(t_command **command)
{
	validate_quotes(command);
	(*command)->rest_string = determine_command(command);
	determine_options(command);
	(*command)->argument = determine_argument(*command);
}

void	parser(t_command **command)
{
	replace_symbol(&(*command)->raw_string, '\n', '\0');
	// semicolon(&(*command)->raw_string);
	determine_struct(command);
}
