/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:20:48 by mismene           #+#    #+#             */
/*   Updated: 2021/05/06 21:11:17 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define NOT_VALID_ID 6
# define IS_DIR 21
# define PERM_DEN 13
# define TOO_HIGH 14

void			copy_to_matrix(char **matrix, char ***pipes, size_t *i);
char			*determine_command_path(t_command *command,
					t_parsed_data *parsed_data, size_t j);
void			fn_redir_helper(t_command *command,
					t_parsed_data *parsed_data, int *error);
int				ft_count_lst(t_env *env);
void			free_four(char **str1, char **str2);
char			***get_pipes(t_command *command);
void			replace_symbol3(char ****array, char old, char new);
void			validate_spaces(char **string);
void			validate_pipe(char **raw_string);
void			validate_q(char *quote, char *p, size_t index);
void			print_array3(char ***array);
int				is_next_redirect(char *string, char type);
char			*determine_filename(char **p, size_t *index,
					char type, int *r_type);
void			move_pointer_to(char **p, char c);
int				open_file(char type, int r_type, char **filename);
int				is_ctrd_allowed(char *str, size_t c_p);
void			new_symbol(char **str, t_command *command,
					int *current, size_t *c_p);
void			ctr_d(void);
void			ctr_c(t_command *command);
int				is_backspace_allowed(char *str, size_t cursor_position);
int				termcap_check(char *str);
void			free_array(char ***array);
char			**get_splitted(char *raw_string);
size_t			array_size(char **array);
char			*mirroring(char *p, char quote);
char			*validate_env_sub(char quote, char *p,
					size_t index, t_env *env);
char			*validate_quote(char *quote, char *p, size_t index);
void			free_memory(t_parsed_data *parsed_data, t_command *command);
void			delete_quotes(char ***splitted);
int				ft_form_file(char *file);
void			ft_delete_word(char **string, size_t start, size_t size);
void			ft_delete_char(char **string, size_t place);
void			ft_insert_str(char **string, char *buf, size_t index);
void			print_array(char **p);
char			**ft_separator(char *string, char c);
void			sort_splitted(char ***splitted);
void			backspace(char **string, size_t *cursor_position);
char			*determine_argument(t_command *command);
void			determine_options(t_command *command);
char			*determine_command(t_command *command);
int				is_current_folder(char	*command);
int				is_build_in(char *command);
int				is_command_bin(t_command *command);
int				validate_command(char **command);
char			*validate_raw_string(char *raw_string);
char			*ft_take_word(char **string);
void			substitution(char **dst, t_env *env);
void			semicolon(t_command *command);
size_t			matrixlen(char **matrix);
int				count_req_chars(char *string, char req);
void			reset_(t_command *command, size_t flag);
t_command		*initialize_command();
t_parsed_data	*initialize_parsed_data(char **env);
void			term_ini();
void			delete_last_charachter(char **string);
void			clear_command_line();
void			replace_symbol(char **string, char old, char new);
void			replace_symbol_array(char	***array, char old, char new);
char			*navigate_history(char **history, char *str, int *current);
void			fn_termcap(t_command *command, char **history);
int				ft_putchar(int c);
void			ft_putstr(const char *str);
void			test_clean_screen(void);
int				termcap_test(int argc, char **argv);
void			spec_symbol(char *buf, t_parsed_data **parsed_data);
void			initialize_structure(t_command *command);
void			pwd(t_command *command);
void			router(t_parsed_data *parsed_data, t_command *command);
void			save_history(t_parsed_data *parsed_data, char *line);
void			parser(t_command *command, t_env *env);
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
void			fn_set_env(t_parsed_data *parsed_data,
					t_command *command, char *tmp, int fl);
t_env			*fn_get_el(t_parsed_data *parsed_data, char *key);
void			fn_unset(t_parsed_data *parsed_data, t_command *command);
char			*fn_strcreate(char *s, int start, int len);
char			*fn_strjoin3(char *str1, char *str2, char *str3);
int				fn_errors(t_command *command, int error);
void			fn_fork(t_parsed_data *parsed_data, t_command *command);
void			fn_zero(char **tmp, t_env **lst,
					char **value, t_env **lst_name);
int				fn_check(char *new_path, t_command *command);
t_env			*create_export(t_parsed_data *parsed_data);
void			fn_get_name(t_env **lst_name, char *value, int flag);
void			fn_get_needed_el(char *tmp, char **value,
					t_env **lst_name, t_parsed_data *parsed_data);
char			**fn_arr(t_env *env);
char			*fn_path(t_parsed_data *parsed_data,
					t_command *command, int *error);
int				fn_redir(t_parsed_data *parsed_data, t_command *command);
void			level(t_parsed_data *parsed_data, t_command *command);
void			fn_pipe(t_parsed_data *parsed_data, t_command *command);
char			*create_str_ex(char *str);
void			proc_signal_handler(int signo);

#endif
