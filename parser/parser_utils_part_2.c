#include "../minishell.h"

void	sort_splitted(char ***splitted)
{
	char	**p;
	size_t	index;
	char	quote;
	size_t	reminder;

	print_array(*splitted);
	quote = '\0';
	p = *splitted;
	index = 0;
	ft_putstr_fd("----------------------\n", 1);
	while (p[index] || quote)
	{
		printf("current element: %s\n", p[index]);
		if (p[index] && (p[index][0] == '\'' || p[index][0] == '"') && !quote)
		{
			quote = p[index][0];
			reminder = index;
		}
		else if (quote)
		{
			p[reminder] = ft_strjoin(p[reminder], p[index]);
			free_str(&p[index]);
			if (p[reminder][ft_strlen(p[reminder]) - 1] == quote)
				quote = '\0';
		}
		index++;
	}
	ft_putstr_fd("----------------------\n", 1);
	print_array(*splitted);
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

int		is_current_folder(char *command)
{
	if (command[0] == '.' && command[1] == '/')
		return (1);
	else
		return (0);
}
