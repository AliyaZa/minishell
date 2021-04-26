#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_parsed_data
{
	char		**history;
	t_env		*env_data;
}				t_parsed_data;

typedef	struct	s_flags
{
	int			is_bin;
	int			rev_redirect;
}				t_flags;

typedef struct	s_command
{
	char 		*raw_string;
	char		*command;
	char		option;
	char		*argument;
	char		*rest_string;
	char		quotes_type;
	char		*queue;
	char		**splited;
	int			fd[2];
	t_flags		*flags;
}				t_command;

#endif
