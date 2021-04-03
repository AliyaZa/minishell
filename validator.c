/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:04:00 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 14:45:58 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_quotes(t_parsed_data **parsed_data)
{
	size_t	quotes_counter;
	char	main_quotes;
	size_t	flag;
	char	*string;

	string = (*parsed_data)->raw_string;
	flag = 0;
	quotes_counter = 0;
	main_quotes = 0;
	while (*string)
	{
		if (*string == '"' || *string == '\'')
		{
			main_quotes = *string;
			if (*string == main_quotes)
				quotes_counter++;
		}
		string++;
	}
	if ((quotes_counter % 2) && main_quotes)
	{
		write(1, ">", 1);
		parser(parsed_data);
	}
}
