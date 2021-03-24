/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/24 18:41:30 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	determine_options(t_parsed_data **parsed_data)
{
	char	option;
	size_t	index;

	index = 0;
	option = 0;
	while ((*parsed_data)->rest_string[index])
	{
		if ((*parsed_data)->rest_string[index] == '-')
		{
			if (ft_isalpha((*parsed_data)->rest_string[index + 1]))
			{
				(*parsed_data)->option = (*parsed_data)->rest_string[index + 1];
				break ;
			}
		}
		index++;
	}
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
	(*parsed_data)->command = (char *)malloc((sizeof(char) * i) + 1);
	ft_strlcpy((*parsed_data)->command, (*parsed_data)->raw_string, (size_t)(i + 1));
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
		if (buf[0] == '\n')
			break ;
		(*parsed_data)->raw_string = ft_strjoin((*parsed_data)->raw_string, buf);
	}
	if ((*parsed_data)->raw_string)
	{
		(*parsed_data)->rest_string = determine_command(parsed_data);
		determine_options(parsed_data);
	}
	printf("command: %s\n", (*parsed_data)->command);
	printf("flag: %c\n", (*parsed_data)->option);
}
