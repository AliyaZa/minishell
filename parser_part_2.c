#include "minishell.h"

int		is_current_folder(char	*command)
{
	if (command[0] == '.' && command[1] == '/')
		return (1);
	else
		return (0);
}

int		is_command_bin(t_command *command)
{
	if (!ft_strncmp(command->command, "/", 1))
		return (1);
	if (!ft_strncmp(command->command, "~", 1))
		return (1);
	if (!ft_strncmp(command->command, ".", 1))
		return (1);
	return (0);
}
