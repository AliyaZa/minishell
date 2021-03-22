#include "minishell.h"

void	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	while (1)
	{
		printf("minishell>");
	
		env_data = parse_env(env);
		parsed_data = parser();
		if (fn_search("echo", parsed_data->command))
		{
			fn_echo(parsed_data->rest_string);
		}
		else if (fn_search(parsed_data->command, "pwd") && *parsed_data->command)
		{
			printf("%s\n", take_value_by_key(env_data, "PWD"));
		}
		else if (fn_search(parsed_data->command, "env") && *parsed_data->command)
		{
			print_env(env_data);
		}
		else if (fn_search(parsed_data->command, "cd"))
		{
			chdir("..");
		}
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
	}
}
