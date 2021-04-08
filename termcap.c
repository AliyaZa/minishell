#include "minishell.h"

void	backspace(char **string, int *cursor_position)
{
	if (*cursor_position)
		delete_last_charachter(string);
	*cursor_position = *cursor_position - 1;
	clear_command_line();
	ft_putstr_fd(*string, 1);
}

void    fn_termcap(t_command **command, char **history)
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
			free((*command)->raw_string);
			(*command)->raw_string = navigate_history(history, &str, &current);
		}
		else if (!ft_strncmp(str, "\e[D", 3) || !ft_strncmp(str, "\e[C", 3))
			;
		else if (!ft_strncmp(str, "\x7f", ft_strlen("\x7f")) || !ft_strncmp(str, "\177", 1))
		{
			backspace(&(*command)->raw_string, &cursor_position);
		}
		else
		{
			ft_putstr_fd(str, 1);
			if (!(*command)->raw_string)
				(*command)->raw_string = ft_strnew(0);
			(*command)->raw_string = ft_strjoin((*command)->raw_string, str);
			current = -1;
		}
	}
}
