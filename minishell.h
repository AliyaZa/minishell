#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "structures.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/dir.h>
# include <sys/syslimits.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>

void			reset_(t_command **command, size_t flag);
t_command		*initialize_command();
t_parsed_data	*initialize_parsed_data(char **env);
void			term_ini();
void			delete_last_charachter(char **string);
void			clear_command_line();
void			replace_symbol(char **string, char old, char new);
char			*navigate_history(char **history, char **str, int *current);
void			fn_termcap(t_command **command, char **history);
int				ft_putchar(int c);
void			ft_putstr(const char *str);
void			test_clean_screen(void);
int				termcap_test(int argc, char **argv);
void			spec_symbol(char *buf, t_parsed_data **parsed_data);
void			initialize_structure(t_command *command);
void			pwd(t_env *env_data);
void			router(t_parsed_data *parsed_data, t_command *command);
void			save_history(t_parsed_data **parsed_data, char *line);
void			parser(t_command **command);
void			free_str(char **s);
int				main_cycle(char **env);
void			print_env(t_env *env_data);
char			*get_value_by_key(t_env *env_data, char *key);
void			fn_echo(t_command *command);
int				fn_search(char *s1, char *s2);
t_env			*parse_env(char **env);
void			validate_quotes(t_command **command);
void			string_tolower(char *string);
char			*ft_strnew(unsigned int size);
size_t			command_len(const char *command);
void			fn_cd(t_command *command, t_parsed_data *parsed_data);

#endif
