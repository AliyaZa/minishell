#include "../minishell.h"

void	print_env(t_env *env_data)
{
	size_t	i;

	i = 0;
	while (env_data->next != NULL)
	{
		ft_putstr_fd(env_data->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env_data->value, 1);
		ft_putstr_fd("\n", 1);
		env_data = env_data->next;
	}
}
