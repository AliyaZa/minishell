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

void	validate_quotes(char *string)
{
	size_t	quotes_counter;
	size_t	double_quotes_counter;
	char	main_quotes;
	size_t	flag;

	flag = 0;
	quotes_counter = 0;
	double_quotes_counter = 0;
	main_quotes = 0;
	while (*string)
	{
		if ((*string == '"' || *string == '\'') && !flag)
		{
			main_quotes = *string;
			flag = 1;
		}
		if (*string == '"' || *string == '\'')
		{
			if (*string == '"')
				double_quotes_counter++;
			else
				quotes_counter++;
		}
		string++;
	}
	if ((double_quotes_counter % 2) && main_quotes == '"')
		printf("close quote\n");
	if ((quotes_counter % 2) && main_quotes == '\'')
		printf("close single quotes\n");
}
