#include "minishell.h"

t_command		*initialize_command()
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	parsed_data->raw_string = ft_strnew(0);
	command->command = NULL;
	command->option = 0;
	command->argument = NULL;
	command->is_in_quotes = 0;
	command->rest_string = 0;
	return (command);
}

t_parsed_data	*initialize_parsed_data()
{
	t_parsed_data	*parsed_data;

	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	parsed_data->history = (char **)malloc(sizeof(char *) * 500);
	parsed_data->env_data = parse_env(env);
	return (parsed_data);
}