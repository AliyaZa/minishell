/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 14:24:42 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*determine_argument(char *string)
{
	char	*argument;

	argument = NULL;
	validate_quotes(string);
	return (argument);
}

char	determine_options(char *string)
{
	char	option;

	option = 0;
	while (*string)
	{
		if (*string == '-')
		{
			string++;
			if (ft_isalpha(*string))
			{
				option = *string;
			}
		}
		string++;
	}
	return (option);
}

char	*determine_command(char *string)
{
	char	*command;
	int		i;

	i = 0;
	while (!(ft_isalpha(*string)))
	{
		string++;
	}
	while (ft_isalpha(string[i]))
	{
		i++;
	}
	command = malloc((sizeof(char) * i) + 1);
	ft_strlcpy(command, string, i);
	string_tolower(command);
	return (command);
}

t_parsed_data	*parser(void)
{
	t_parsed_data	*parsed_data;
	char			*buf;

	parsed_data = malloc(sizeof(t_parsed_data));
	buf = ft_strnew(0);
	parsed_data->raw_string = ft_strnew(0);
	if (buf == NULL)
		return (NULL);
	if (parsed_data == NULL)
		return (NULL);
	while (read(0, buf, 1))
	{
		if (buf[0] == '\n')
			break ;
		parsed_data->raw_string = ft_strjoin(parsed_data->raw_string, buf);
	}
	parsed_data->command = determine_command(parsed_data->raw_string);
	parsed_data->option = determine_options(parsed_data->raw_string);
	parsed_data->argument = determine_argument(parsed_data->raw_string);
	printf("command - %s\n", parsed_data->command);
	printf("flag - %c\n", parsed_data->option);
	return (parsed_data);
}
