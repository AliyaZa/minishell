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

void	delete_last_charachter(char **string)
{
	size_t	strlen;

	strlen = ft_strlen(*string);
	strlen -= 1;
	(*string)[strlen] = '\0';
}

int		count_req_chars(char *string, char req)
{
	int	counter;
	int	index;

	counter = 0;
	index = 0;
	while (string[index])
	{
		if (string[index] == req)
			counter++;
		index++;
	}
	return (counter);
}

char	*ft_take_word(char **string)
{
	int		index;
	char	*p;
	int		start;

	p = *string;
	index = 0;
	while (p[index] == ' ')
		index++;
	start = index;
	while(p[index] && (ft_isalpha(p[index]) || ft_isdigit(p[index])))
		index++;
	*string = &p[index];
	return (ft_substr(p, start, index));
}