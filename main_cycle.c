#include "minishell.h"

void	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	parsed_data = malloc(sizeof(t_parsed_data));
	parsed_data->user_commands = (char **)malloc(sizeof(char *) * 500);
	if (!parsed_data->user_commands)
		return ;
	while (1)
	{
		env_data = parse_env(env);
		parser(&parsed_data);
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
		save_history(&parsed_data);
		printf("%s\n", parsed_data->user_commands[0]);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
	}
}
