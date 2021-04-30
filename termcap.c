#include "minishell.h"

void	ctr_d(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	new_symbol(char **str, t_command **command, int *current)
{
	ft_putstr_fd(*str, 1);
	if (!(*command)->raw_string)
		(*command)->raw_string = ft_strnew(0);
	(*command)->raw_string = ft_strjoin_free((*command)->raw_string, *str, 1);
	*current = -1;
}

void	fn_termcap(t_command **command, char **history)
{
	int			l;
	char		*str;
	static int	current;
	int			cursor_position;

	current = -1;
	str = ft_calloc(2000, sizeof(char));
	str[0] = 0;
	cursor_position = 0;
	while (str[0] != '\n')
	{
		l = read(0, str, 1998);
		if (ft_strncmp_end(str, "\x03", 1))
			cursor_position += l;
		str[l] = 0;
		if (!ft_strncmp_end(str, "\x04", 1) && cursor_position == 1)
			ctr_d();
		else if (!ft_strncmp(str, "\x03", 1))
		{
			free((*command)->raw_string);
			(*command)->raw_string = ft_strnew(0);
			ft_putstr_fd("\nminishell> ", 1);
			tputs(save_cursor, 1, ft_putchar);
		}
		else if (!ft_strncmp(str, "\e[A", 3) || !ft_strncmp(str, "\e[B", 3))
		{
			free((*command)->raw_string);
			(*command)->raw_string = navigate_history(history, &str, &current);
		}
		else if (!ft_strncmp(str, "\e[D", 3) || !ft_strncmp(str,
		"\e[C", 3) || !ft_strncmp(str, "\t", 1) || !ft_strncmp(str, "\034", 2))
			;
		else if ((!ft_strncmp_end(str, "\177", 1) && !ft_strncmp(str, "\x7f",
		ft_strlen("\x7f"))) || !ft_strncmp(str, "\177", 1))
			backspace(&(*command)->raw_string, &cursor_position);
		else
			new_symbol(&str, command, &current);
	}
}
