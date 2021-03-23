/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/23 17:33:13 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*determine_argument(char *string)
{
	char	*argument;

	argument = NULL;
	validate_quotes(string);
	while (*string)
	{
		if (*string == '\'' || *string == '"')
		{
			argument = ft_strdup(string);
			break ;
		}
		string++;
	}
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

char	*determine_command(t_parsed_data **parsed_data)
{
	int		i;
	char	*p;

	p = (*parsed_data)->raw_string;
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
	(*parsed_data)->command = malloc((sizeof(char) * i) + 1);
	(*parsed_data)->raw_string[i] = '\0';
	ft_strlcpy((*parsed_data)->command, (*parsed_data)->raw_string);
	string_tolower((*parsed_data)->command);
	return (p);
}

void	parser(t_parsed_data **parsed_data)
{
	char			*buf;

	buf = ft_strnew(0);
	(*parsed_data)->raw_string = ft_strnew(0);
	if (buf == NULL)
		return ;
	if (parsed_data == NULL)
		return ;
	while (read(0, buf, 1))
	{
		if (buf[0] == '\n' || buf[0] == '\0')
			break ;
		(*parsed_data)->raw_string = ft_strjoin((*parsed_data)->raw_string, buf);
	}
	if ((*parsed_data)->raw_string)
	{
		(*parsed_data)->rest_string = determine_command(parsed_data);
	}
	else
	{
		printf("hello bro\n");
	}
}
