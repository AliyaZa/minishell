#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

# define VIOLET "\033[25m"
# define COLOUR_END "\033[m"

typedef struct	s_parsed_data
{
	char 		*raw_string;
	char		*command;
	char		option;
	char		*argument;
	char		*rest_string;
	char		**user_commands;
}				t_parsed_data;

void			router(t_parsed_data *parsed_data, t_env *env_data);
void			save_history(t_parsed_data **parsed_data);
void			parser(t_parsed_data **parsed_data);
void			free_str(char **s);
void			main_cycle(char **env);
void			print_env(t_env *env_data);
char			*get_value_by_key(t_env *env_data, char *key);
void			fn_echo(char *parsed_data);
int				fn_search(char *s1, char *s2);
t_env			*parse_env(char **env);
void			validate_quotes(char *string);
void			string_tolower(char *string);
char			*ft_strnew(unsigned int size);
size_t			command_len(const char *command);

#endif
