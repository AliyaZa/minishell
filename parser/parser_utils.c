/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_part_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:37:14 by mismene           #+#    #+#             */
/*   Updated: 2021/04/27 14:37:15 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	determine_rest_string(t_command *command, size_t index)
{
	size_t	strlen;

	strlen = ft_strlen(command->rest_string);
	while (command->option == 'n' && index > 0)
	{
		command->rest_string++;
		index--;
	}
	while (!(ft_isprint(*command->rest_string))
		&& (*command->rest_string != ' ') && strlen)
	{
		if (*command->rest_string == command->option)
			command->rest_string++;
		command->rest_string++;
	}
}

char	*determine_argument(t_command *command)
{
	char	*arg;
	size_t	index;

	arg = command->rest_string;
	index = 0;
	if (command->option == 'n')
	{
		arg = ft_strchr(command->rest_string, command->option);
		arg++;
	}
	while ((!(ft_isprint(*arg)) && ft_strlen(arg)) || (*arg == ' '))
		arg++;
	return (arg);
}

char	*determine_command(t_command *command)
{
	int		i;
	char	*p;
	char	*command_p;

	p = command->raw_string;
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
	command->command = ft_substr(command_p, 0, i);
	string_tolower(command->command);
	return (p);
}

void	determine_options(t_command *command)
{
	char	option;
	size_t	index;

	index = 0;
	option = 0;
	while (command->rest_string[index])
	{
		if (command->rest_string[index] == '-')
		{
			if (ft_isalpha(command->rest_string[index + 1]))
			{
				if (command->rest_string[index + 2] == ' ')
					command->option = command->rest_string[index + 1];
				break ;
			}
		}
		index++;
	}
	determine_rest_string(command, index);
}

char		**get_splitted(char *raw_string)
{
	char	*p;
	size_t	index;
	char	quote;
	int		flag;

	p = raw_string;
	quote = '\0';
	index = 0;
	flag = 0;
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
		{
			if (!quote)
				quote = p[index];
			else if (quote == p[index])
				quote = 0;
		}
		if ((p[index] == '>' || p[index] == '<') && !quote)
		{
			if (p[index] == '>')
				while (p[index] && flag != 2)
				{
					ft_delete_char(&p, index);
					if (ft_isprint(p[index]) && p[index] != ' ' && !flag)
						flag++;
					if (flag == 1 && p[index] == ' ')
						flag++;
				}
			else
				ft_delete_char(&p, index);
			continue ;
		}
		index++;
	}
	return (ft_split(p, ' '));
}
