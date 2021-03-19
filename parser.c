/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 11:00:49 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("%s\n", command);
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
	return (parsed_data);
}
