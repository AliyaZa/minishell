#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/dir.h>
# include <sys/syslimits.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>


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

void			determine_struct(t_parsed_data **parsed_data);
void			fn_termcap(t_parsed_data **parsed_data);
int				ft_putchar(int c);
void			ft_putstr(const char *str);
void			test_clean_screen(void);
int				termcap_test(int argc, char **argv);
void			spec_symbol(char *buf, t_parsed_data **parsed_data);
void			initialize_structure(t_parsed_data *parsed_data);
void			pwd(t_env *env_data);
void			fn_cd(t_env **our_env, char *parsed_data);
void			router(t_parsed_data *parsed_data);
void			save_history(t_parsed_data **parsed_data);
void			parser(t_parsed_data **parsed_data);
void			free_str(char **s);
void			main_cycle(char **env);
void			print_env(t_env *env_data);
char			*get_value_by_key(t_env *env_data, char *key);
void			fn_echo(t_parsed_data *parsed_data);
int				fn_search(char *s1, char *s2);
t_env			*parse_env(char **env);
void			validate_quotes(t_parsed_data **parsed_data);
void			string_tolower(char *string);
char			*ft_strnew(unsigned int size);
size_t			command_len(const char *command);

#endif
