#include "../minishell.h"

void	print_env(t_env *env_data, t_command *command)
{
	size_t	i;

	i = 0;
	while (env_data != NULL)
	{
		if (!env_data->equal)
		{
			ft_putstr_fd(env_data->key, command->fd[1]);
			ft_putstr_fd("=", command->fd[1]);
			ft_putstr_fd(env_data->value, command->fd[1]);
			ft_putstr_fd("\n", command->fd[1]);
		}
		env_data = env_data->next;
	}
}
