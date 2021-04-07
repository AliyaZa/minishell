#include "minishell.h"

char	*navigate_history(char **history, char **str, int *current)
{
	int next;

	next = !ft_strncmp(*str, "\e[A", 3) ? 1 : -1;
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
		return (ft_strdup(history[*current]));
	}
	return (NULL);
}