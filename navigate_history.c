#include "minishell.h"

void	clear_command_line()
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
}

void	navigate_history(char **history, int next, int *current)
{
	if (*current == 0 && next == -1)
	{
		clear_command_line();
		*current = -1;
	}
	else if (history[*current + next])
	{
		*current += next;
		clear_command_line();
		ft_putstr_fd(history[*current], 1);
	}
}