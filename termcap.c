#include "minishell.h"

void	write_history_command(char **history, int *current, char direction)
{
	int		next;

	next = direction == 'u' ? 1 : -1;
	if (history[*current + next])
	{
		*current += next;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, history[*current], ft_strlen(history[*current]));
	}
	if (*current == 0 && direction == 'd')
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
	}
}

void    fn_termcap(t_parsed_data **parsed_data)
{
	int		l;
	static int	current;
	char	str[2000];

	current = -1;
	str[0] = 0;
	while ((ft_strncmp(str, "\x04", 1)) && !(str[0] == '\n'))
	{
		l = read(0, str, 100);
		str[l] = 0;
		if (!ft_strncmp(str, "\e[A", 3))
		{
			write_history_command((*parsed_data)->history, &current, 'u');
		}
		else if (!ft_strncmp(str, "\e[B", 3))
		{
			write_history_command((*parsed_data)->history, &current, 'd');
		}
		else if (!ft_strncmp(str, "\e[D", 3))
		{
			tputs(cursor_left, 1, ft_putchar);
		}
		else if (!ft_strncmp(str, "\e[C", 3))
		{
			tputs(cursor_right, 1, ft_putchar);
		}
		else if (!ft_strncmp(str, "\x7f", ft_strlen("\x7f")) || !ft_strncmp(str, "\177", 1))
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
		}
		else
		{
			write(1, str, l);
			(*parsed_data)->raw_string = ft_strjoin((*parsed_data)->raw_string, str);
		}
	}
}
