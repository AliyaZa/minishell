#include "minishell.h"

void    fn_termcap(t_parsed_data **parsed_data)
{
	int			l;
	char		*str;
	static int	current;
	int			cursor_position;

	current = -1;
	str = ft_calloc(2000, sizeof(char));
	str[0] = 0;
	cursor_position = 0;
	while ((ft_strncmp(str, "\x04", 1)) && !(str[0] == '\n'))
	{
		l = read(0, str, 100);
		cursor_position += l;
		str[l] = 0;
		if (!ft_strncmp(str, "\e[A", 3) || !ft_strncmp(str, "\e[B", 3))
		{
			free((*parsed_data)->raw_string);
			(*parsed_data)->raw_string = navigate_history((*parsed_data)->history, &str, &current);
		}
		else if (!ft_strncmp(str, "\e[D", 3) || !ft_strncmp(str, "\e[C", 3))
			;
		else if (!ft_strncmp(str, "\x7f", ft_strlen("\x7f")) || !ft_strncmp(str, "\177", 1))
		{
			if (cursor_position)
				delete_last_charachter(parsed_data);
			cursor_position--;
			clear_command_line();
			ft_putstr_fd((*parsed_data)->raw_string, 1);
		}
		else
		{
			ft_putstr_fd(str, 1);
			if (!(*parsed_data)->raw_string)
				(*parsed_data)->raw_string = ft_strnew(0);
			(*parsed_data)->raw_string = ft_strjoin((*parsed_data)->raw_string, str);
			current = -1;
		}
	}
}
