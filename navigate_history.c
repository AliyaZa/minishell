/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:39:35 by mismene           #+#    #+#             */
/*   Updated: 2021/04/27 14:39:40 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*navigate_history(char **history, char **str, int *current)
{
	int		next;
	char	*string;

	next = !ft_strncmp(*str, "\e[A", 3) ? 1 : -1;
	if (*current == 0 && next == -1)
	{
		clear_command_line();
		*current = -1;
	}
	else if (history[*current + next])
	{
		*current += next;
		clear_command_line();
		string = history[*current];
		replace_symbol(&string, '\n', '\0');
		ft_putstr_fd(string, 1);
		return (ft_strdup(history[*current]));
	}
	return (NULL);
}
