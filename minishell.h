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
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# define COMMAND_NOT_FOUND 1
# define NOT_AN_EXECUTABLE_FILE 4
# define SYNTAX_ERROR 3
# define IS_FILE 5

char			*ft_take_word(char **string);
void			substitution(char **dst, t_env *env);
void			semicolon(t_command **command);
size_t			matrixlen(char **matrix);
int				count_req_chars(char *string, char req);
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
void			pwd(t_command *command);
void			router(t_parsed_data *parsed_data, t_command *command);
void			save_history(t_parsed_data **parsed_data, char *line);
void			parser(t_command **command, t_env *env);
void			free_str(char **s);
int				main_cycle(char **env);
void			print_env(t_env *env_data, t_command *command);
char			*get_value_by_key(t_env *env_data, char *key);
void			fn_echo(t_command *command);
int				fn_search(char *s1, char *s2);
t_env			*parse_env(char **env);
void			validator(char **string, t_env *env, t_command *command);
void			string_tolower(char *string);
char			*ft_strnew(unsigned int size);
size_t			command_len(const char *command);
void			fn_cd(t_command *command, t_parsed_data *parsed_data);
void			fn_export(t_parsed_data *parsed_data, t_command *command);
void			fn_set_env(t_parsed_data *parsed_data, t_command *command, char *tmp, int fl);
t_env			*fn_get_el(t_parsed_data *parsed_data, char *key);
void			fn_unset(t_parsed_data *parsed_data, t_command *command);
char			*fn_strcreate(char *s, int start, int len);
char			*fn_strjoin3(char *str1, char *str2, char *str3);
int				fn_errors(t_command *command, int error);
void			fn_fork(t_parsed_data *parsed_data, t_command *command);
void			fn_zero(char **tmp, t_env **lst, char **value, t_env **lst_name);
int				fn_check(char *new_path, t_command *command);

#endif
