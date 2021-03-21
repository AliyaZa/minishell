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
	char		option;
	char		*argument;
	char		*rest_string;
}				t_parsed_data;

t_parsed_data	*parser();

void			print_env(t_env *env_data);
char			*take_value_by_key(t_env *env_data, char *key);
void			fn_echo(char *parsed_data);
int				fn_search(char *s1, char *s2);
t_env			*parse_env(char **env);
void			validate_quotes(char *string);
void			string_tolower(char *string);
char			*ft_strnew(unsigned int size);
size_t			command_len(const char *command);

#endif
