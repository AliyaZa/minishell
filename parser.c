/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 11:36:05 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			determine_options(char *string)
{
	size_t	i;
	char	f;

	i = 0;
	f = 0;
	while (*string)
	{
		if (*string == '-' && i == 1)
		{
			string++;
			if (ft_isalpha(*string))
			{
				f = 'n';
			}
		}
		if (*string == ' ')
		{
			i = i + 1;
		}
		string++;
	}
	return (f);	
}

char			*determine_command(char *string)
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

t_parsed_data	*parser()
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
	printf("command - %s\n", parsed_data->command);
	printf("flag - %c\n", parsed_data->option);
	return (parsed_data);
}
