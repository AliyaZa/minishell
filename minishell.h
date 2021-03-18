#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_parsed_data
{
	char *		user_string;
}				t_parsed_data;

t_parsed_data	*parser();

#endif
