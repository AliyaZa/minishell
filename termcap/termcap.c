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

int			read_user_input(char **str)
{
	int		l;
	char	*p;

	p = *str;
	l = read(0, p, 1998);
	p[l] = 0;
	return (l);
}

t_termcap	*termcap_ini(void)
{
	t_termcap	*term;

	term = malloc(sizeof(term));
	term->current = -1;
	term->str = ft_calloc(2000, sizeof(char));
	term->str[0] = 0;
	term->cursor_position = 1;
	return (term);
}

void		termcap_conditions(t_termcap *term, t_command *command)
{
	if (termcap_check(term->str))
		;
	else if (is_backspace_allowed(term->str, term->cursor_position))
		backspace(&command->raw_string, &term->cursor_position);
	else if (term->l > 0 && ft_strncmp(term->str, "\x04", 1))
		new_symbol(&term->str,
			command, &term->current, &term->cursor_position);
}

void		fn_termcap(t_command *command, char **history)
{
	t_termcap	*term;

	term = termcap_ini();
	while (term->str[0] != '\n')
	{
		term->l = read_user_input(&term->str);
		if (is_ctrd_allowed(term->str, term->cursor_position))
			ctr_d();
		else if (!ft_strncmp(term->str, "\x03", 1))
			ctr_c(command);
		else if (!ft_strncmp(term->str, "\e[A", 3)
			|| !ft_strncmp(term->str, "\e[B", 3))
		{
			free(command->raw_string);
			command->raw_string = navigate_history(history,
				term->str, &term->current);
			term->cursor_position += ft_strlen(command->raw_string);
		}
		else
			termcap_conditions(term, command);
	}
	free(term->str);
	free(term);
}
