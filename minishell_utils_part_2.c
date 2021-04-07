/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_part_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:35:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/22 14:45:24 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

int		ft_putchar(int c)
{
	if (write(1, &c, 1))
		return (0);
	return (-1);
}

void	replace_symbol(char **string, char old, char new)
{
	char	*p_n;
	if ((p_n = ft_strchr(*string, old)))
		*p_n = new;
}

void	delete_last_charachter(t_parsed_data **parsed_data)
{
	size_t	strlen;

	strlen = ft_strlen((*parsed_data)->raw_string);
	strlen -= 1;
	(*parsed_data)->raw_string[strlen] = '\0';
}