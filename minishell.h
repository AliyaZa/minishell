#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct	s_parsed_data
{
	char 		*raw_string;
}				t_parsed_data;

t_parsed_data	*parser();
char			*ft_strnew(unsigned int size);

#endif
