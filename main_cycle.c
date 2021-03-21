#include "minishell.h"

void	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	env_data = parse_env(env);
	parsed_data = parser();
	if (fn_search(parsed_data->command, "echo"))
	{
		fn_echo(parsed_data->rest_string);
	}
	else if (fn_search(parsed_data->command, "pwd"))
	{
		printf("%s\n", take_value_by_key(env_data, "PWD"));
	}
	else if (fn_search(parsed_data->command, "env"))
	{
		print_env(env_data);
	}
}
