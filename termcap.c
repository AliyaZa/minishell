#include "minishell.h"

void    fn_termcap(t_parsed_data **parsed_data)
{
	int		l;
	char	str[2000];
	static int	current;

	str[0] = 0;
	current = -1;
	while ((ft_strncmp(str, "\x04", 1)) && !(str[0] == '\n'))
	{
		l = read(0, str, 100);
		str[l] = 0;
		if (!ft_strncmp(str, "\e[A", 3))
		{
			navigate_history((*parsed_data)->history, 1, &current);
		}
		else if (!ft_strncmp(str, "\e[B", 3))
		{
			navigate_history((*parsed_data)->history, -1, &current);
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
