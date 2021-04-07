/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/04/05 18:33:01 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*determine_argument(t_parsed_data *parsed_data)
{
	char	*arg;
	size_t	index;

	arg = parsed_data->rest_string;
	index = 0;
	if (parsed_data->option)
	{
		arg = ft_strchr(parsed_data->rest_string, parsed_data->option);
		arg++;
	}
	while (!(ft_isprint(*arg)) && (*arg != ' ') && ft_strlen(arg))
		arg++;
	while ((arg[index] != '\"' && arg[index] != ';' && arg[index] != '\n') && parsed_data->is_in_quotes)
	{
		index++;
	}
	if (parsed_data->is_in_quotes)
		arg[index] = 0;
	return (arg);
}

void	determine_rest_string(t_parsed_data **parsed_data, size_t index)
{
	size_t	strlen;
	
	strlen = ft_strlen((*parsed_data)->rest_string);
	while ((*parsed_data)->option == 'n' && index > 0)
	{
		(*parsed_data)->rest_string++;
		index--;
	}
	while (!(ft_isprint(*(*parsed_data)->rest_string)) && (*(*parsed_data)->rest_string != ' ') && strlen)
	{
		if (*(*parsed_data)->rest_string == (*parsed_data)->option)
			(*parsed_data)->rest_string++;
		(*parsed_data)->rest_string++;
	}
}

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
	determine_rest_string(parsed_data, index);
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

void	determine_struct(t_parsed_data **parsed_data)
{
	validate_quotes(parsed_data);
	(*parsed_data)->rest_string = determine_command(parsed_data);
	determine_options(parsed_data);
	(*parsed_data)->argument = determine_argument(*parsed_data);
}



void	parser(t_parsed_data **parsed_data)
{
	replace_symbol(&(*parsed_data)->raw_string, '\n', '\0');
	determine_struct(parsed_data);
}
