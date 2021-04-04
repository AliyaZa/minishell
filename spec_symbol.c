#include "minishell.h"

void	spec_symbol(char *buf, t_parsed_data **parsed_data)
{
	if (*buf == ';')
		router(*parsed_data);
	// parsed_data->rest_string = determine_command(parsed_data);
	// determine_options(parsed_data);
	// parsed_data->argument = determine_argument(parsed_data);
	// write(1, parsed_data->command, ft_strlen(parsed_data->command));
}