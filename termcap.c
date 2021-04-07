#include "minishell.h"

void    fn_termcap(t_parsed_data **parsed_data)
{
	int		l;
	char	*str;
	static int	current;

	current = -1;
	str = calloc(2000, sizeof(char));
	str[0] = 0;
	while ((ft_strncmp(str, "\x04", 1)) && !(str[0] == '\n'))
	{
		l = read(0, str, 100);
		str[l] = 0;
		if (!ft_strncmp(str, "\e[A", 3) || !ft_strncmp(str, "\e[B", 3))
		{
			free((*parsed_data)->raw_string);
			(*parsed_data)->raw_string = navigate_history((*parsed_data)->history, &str, &current);
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
			if (!(*parsed_data)->raw_string)
				(*parsed_data)->raw_string = ft_strnew(0);
			(*parsed_data)->raw_string = ft_strjoin((*parsed_data)->raw_string, str);
			current = -1;
		}
	}
}
