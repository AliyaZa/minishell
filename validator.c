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

void	quotes_stack(char *string, size_t quotes_count)
{	
	char	main_quotes;
	char	*stack;
	int		index;

	index = 0;
	stack = malloc(sizeof(char) * quotes_count + 5);
	stack[quotes_count] = 0;
	if (!stack)
	{
		ft_putstr_fd("memory not allocated", 1);
		return ;
	}
	main_quotes = 0;
	while (*string)
	{
		if (*string == '"' || *string == '\'')
		{
			stack[index++] = *string;
			main_quotes = *string;
		}
		string++;
	}
	printf("%s\n", stack);
}

void	validate_quotes(char *string)
{
	size_t	d_quotes;
	size_t	quotes;

	d_quotes = count_req_chars(string, '"');
	quotes = count_req_chars(string, '\'');
	if ((quotes % 2) || (d_quotes % 2))
		ft_putstr_fd("minishell: syntax error: unexpected end of file", 1);
	quotes_stack(string, d_quotes + quotes);
}
