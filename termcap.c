#include "minishell.h"

void    fn_termcap(t_parsed_data **parsed_data)
{
	int		l;
	char	str[2000];
	struct	termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");

	tputs(save_cursor, 1, ft_putchar);
	while ((ft_strncmp(str, "\x04", 1)) && !(str[0] == '\n'))
	{
		l = read(0, str, 100);
		//printf("%d\n", l);
		if (!ft_strncmp(str, "\e[A", 3))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			write(1, "prev\n", 5);
		}
		else if (!ft_strncmp(str, "\e[B", 3))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			write(1, "next\n", 5);
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
		}
		(*parsed_data)->raw_string = ft_strdup(str);
	}
}
