#include "minishell.h"

void	print_env(t_env *env_data)
{
	size_t	i;

	i = 0;
	while (env_data->next != NULL)
	{
		printf("%s=%s\n", env_data->key, env_data->value);
		env_data = env_data->next;
	}
}
