#include "../minishell.h"

void	ctr_c(t_command *command)
{
	free(command->raw_string);
	command->raw_string = ft_strnew(0);
	ft_putstr_fd("\nminishell> ", 1);
	tputs(save_cursor, 1, ft_putchar);
}

void	ctr_d(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	new_symbol(char **str, t_command *command, int *current, size_t *c_p)
{
	if (!ft_strncmp(*str, "\x7f", ft_strlen("\x7f")) && *c_p < 2)
		;
	else
	{
		ft_putstr_fd(*str, 1);
		if (!command->raw_string)
			command->raw_string = ft_strnew(0);
		command->raw_string = ft_strjoin_free(command->raw_string, *str, 1);
		*current = -1;
		*c_p += ft_strlen(*str);
	}
}

int			is_ctrd_allowed(char *str, size_t c_p)
{
	return (!ft_strncmp(str, "\x04", 1) && c_p == 1);
}
