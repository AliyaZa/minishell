#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct	s_parsed_data
{
	char 		*raw_string;
	char		*command;
	char		**options;
}				t_parsed_data;

t_parsed_data	*parser();

void			string_tolower(char *string);
char			*ft_strnew(unsigned int size);
size_t			command_len(const char *command);

#endif
