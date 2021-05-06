/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:43:35 by mismene           #+#    #+#             */
/*   Updated: 2021/04/27 14:43:37 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	backspace(char **string, size_t *cursor_position)
{
	if (*cursor_position)
		delete_last_charachter(string);
	*cursor_position = *cursor_position - 1;
	clear_command_line();
	ft_putstr_fd(*string, 1);
}

void	term_ini(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ISIG);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
}

void	clear_command_line(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
}

int		termcap_check(char *str)
{
	return (!ft_strncmp(str, "\e[D", 3) || !ft_strncmp(str,
		"\e[C", 3) || !ft_strncmp(str, "\t", 1) || !ft_strncmp(str, "\034", 2)
		|| !ft_strncmp(str, "\v", 1) || !ft_strncmp(str, "\b", 1));
}

int		is_backspace_allowed(char *str, size_t cursor_position)
{
	return (((!ft_strncmp_end(str, "\177", 1))
			|| (!ft_strncmp(str, "\x7f", 1))
			|| (!ft_strncmp(str, "\177", 1)))
			&& (cursor_position > 1));
}
