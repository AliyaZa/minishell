/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:51:59 by mismene           #+#    #+#             */
/*   Updated: 2021/05/04 10:52:01 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			is_ctrd_allowed(char *str, size_t c_p)
{
	return (!ft_strncmp(str, "\x04", 1) && c_p == 1);
}

void		fn_termcap(t_command *command, char **history)
{
	int			l;
	char		*str;
	static int	current;
	size_t		cursor_position;

	current = -1;
	str = ft_calloc(2000, sizeof(char));
	str[0] = 0;
	cursor_position = 1;
	while (str[0] != '\n')
	{
		l = read(0, str, 1998);
		str[l] = 0;
		if (is_ctrd_allowed(str, cursor_position))
			ctr_d();
		else if (!ft_strncmp(str, "\x03", 1))
			ctr_c(command);
		else if (!ft_strncmp(str, "\e[A", 3) || !ft_strncmp(str, "\e[B", 3))
		{
			free(command->raw_string);
			command->raw_string = navigate_history(history, str, &current);
			size_t len = ft_strlen(command->raw_string);
			cursor_position += len;
		}
		else if (termcap_check(str))
			;
		else if (is_backspace_allowed(str, cursor_position))
			backspace(&command->raw_string, &cursor_position);
		else if (l > 0 && ft_strncmp(str, "\x04", 1))
			new_symbol(&str, command, &current, &cursor_position);
	}
}
