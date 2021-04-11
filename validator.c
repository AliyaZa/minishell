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

void	quotes_stack(char *string)
{	
	char	main_quotes;

	main_quotes = 0;
	while (*string)
	{
		if (*string == '"' || *string == '\'')
		{
			main_quotes = *string;
		}
		string++;
	}
}

void	validate_quotes(char *string)
{
	size_t	d_quotes;
	size_t	quotes;

	d_quotes = count_req_chars(string, '"');
	quotes = count_req_chars(string, '\'');
	if ((quotes % 2) || (d_quotes % 2))
		ft_putstr_fd("minishell: syntax error: unexpected end of file", 1);
	quotes_stack(string);
}
