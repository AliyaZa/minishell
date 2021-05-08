/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:04:00 by mismene           #+#    #+#             */
/*   Updated: 2021/04/24 18:38:22 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_word(size_t index, char **p, char **argument)
{
	char	*buf;

	buf = ft_substr(*p, 0, ft_strlen_c(*p, '>'));
	if (ft_strlen(buf))
	{
		*argument = ft_strjoin(*argument, buf);
		ft_delete_word(p, index - 1, ft_strlen(buf));
	}
}

int		redirect(char **string, char type, size_t i, char **argument)
{
	int		fd;
	char	*filename;
	size_t	index;
	int		r_type;
	char	*p;

	p = &(*string)[i];
	index = 0;
	filename = NULL;
	while (p[index])
	{
		index = 0;
		filename = determine_filename(&p, &index, type, &r_type);
		replace_word(index, &p, argument);
		move_pointer_to(&p, '>');
		fd = open_file(type, r_type, &filename);
		if ((!p || ft_strlen(p) == 0) && !is_next_redirect(p, type))
			return (fd);
		else
			close(fd);
	}
	return (fd);
}

void	redirect_logic(char **p, int index, t_command *command, char **string)
{
	char	*tmp;
	char	*pp;

	pp = *p;
	pp[index] == '<' ? command->flags->rev_redirect = 1 : 1;
	tmp = *string;
	*string = ft_substr(pp, 0, index);
	if (!command->flags->rev_redirect)
	{
		command->fd[0] = ft_form_file(pp);
		command->fd[1] = redirect(p, pp[index], index, string);
	}
	else
	{
		command->fd[0] = redirect(p, pp[index], index, string);
		command->fd[1] = ft_form_file(pp);
	}
	tmp = pp;
	pp = ft_strdup(*string);
}

void	validator(char **string, t_env *env, t_command *command)
{
	char	*p;
	size_t	index;
	char	quote;

	index = 0;
	p = ft_strdup(*string);
	quote = '\0';
	while (p[index] && ft_strlen(p))
	{
		if (p[index] == '"' || p[index] == '\'')
			p = validate_quote(&quote, p, index--);
		else if ((p[index] == '$' && (quote == 0 || quote == '"'))
		&& (p[index + 1] != ' ' || p[index + 1] != '\0'))
			p = validate_env_sub(quote, p, index--, env);
		else if ((!ft_strncmp(&p[index], "<", 1)
			|| !ft_strncmp(&p[index], ">", 1)) && !quote)
			redirect_logic(&p, index, command, string);
		else if (p[index] == '\\')
			p = mirroring(p, quote);
		index++;
	}
	if (quote)
		fn_errors(command, SYNTAX_ERROR);
	*string = ft_strdup(p);
	free(p);
}
