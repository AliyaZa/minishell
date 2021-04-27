#include "minishell.h"

void	determine_command_struct(t_command **command, t_env *env)
{
	(*command)->rest_string = determine_command(command);
	if (validate_command(&(*command)->command))
		fn_errors(*command, SYNTAX_ERROR);
	(*command)->flags->is_bin = is_command_bin(*command);
	determine_options(command);
	(*command)->argument = determine_argument(*command);
	validator(&(*command)->argument, env, *command);
}

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
