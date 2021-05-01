#include "../minishell.h"

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

int		is_current_folder(char *command)
{
	if (command[0] == '.' && command[1] == '/')
		return (1);
	else
		return (0);
}

int		is_build_in(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		return (1);
	if (!ft_strncmp(command, "pwd", 3))
		return (1);
	if (!ft_strncmp(command, "env", 3))
		return (1);
	if (!ft_strncmp(command, "cd", 2))
		return (1);
	if (!ft_strncmp(command, "export", 6))
		return (1);
	if (!ft_strncmp(command, "unset", 5))
		return (1);
	if (!ft_strncmp(command, "exit", 4))
		return (1);
	return (0);
}

void	replace_symbol_array(char	***array, char old, char new)
{
	char	**p;
	size_t	index;

	p = *array;
	index = 0;
	while (p[index])
	{
		while (ft_strchr(p[index], old))
			replace_symbol(&p[index], old, new);
		index++;
	}
}

void		delete_quotes(char ***splitted)
{
	char	**p;
	size_t	i;
	char	quote;

	i = 0;
	p = *splitted;
	while (p[i])
	{
		if (p[i][0] == '\'' || p[i][0] == '"')
		{
			quote = p[i][0];
			if (p[i][0] == quote && (p[i][ft_strlen(p[i]) - 1] == quote))
			{
				ft_delete_char(&p[i], 0);
				ft_delete_char(&p[i], ft_strlen(p[i]) - 1);
			}
		}
		i++;
	}
}
