#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_parsed_data
{
	char 		*raw_string;
	char		*command;
	char		option;
	char		*argument;
	char		*rest_string;
	char		**history;
	size_t		is_in_quotes;
	t_env		*env_data;
}				t_parsed_data;



#endif