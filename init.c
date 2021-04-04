#include "minishell.h"

void	initialize_structure(t_parsed_data *parsed_data)
{
	parsed_data->raw_string = NULL;
	parsed_data->command = NULL;
	parsed_data->option = 0;
	parsed_data->argument = NULL;
	parsed_data->history = NULL;
	parsed_data->is_in_quotes = 0;
}