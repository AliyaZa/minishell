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

int		is_next_redirect(char *string, char type)
{
	int		index;

	index = 0;
	while (string[index])
	{
		if (string[index] == type)
			return (1);
		else if (string[index] == '"' || string[index] == '\'')
			return (0);
		index++;
	}
	return (0);
}

int		redirect(char **string, char type, size_t i, char **argument)
{
	int		fd;
	char	*filename;
	size_t	index;
	int		r_type;
	char	*buf;
	char	*p;
	int		kc;
	char	*tmp;

	p = &(*string)[i];
	buf = NULL;
	index = 0;
	filename = NULL;
	while (p[index])
	{
		kc = 0;
		r_type = 0;
		index = 0;
		while (p[index] == ' ' || p[index] == type)
		{
			if (p[index] == type)
			{
				r_type++;
				kc++;
			}
			index++;
		}
		tmp = p;
		p = ft_substr(p, kc, ft_strlen(p));
		// free(tmp);
		filename = ft_take_word(&p);
		buf = ft_substr(p, 0, ft_strlen_c(p, '>'));
		if (ft_strlen(buf))
		{
			// free(*argument);
			*argument = ft_strjoin(*argument, buf);
			ft_delete_word(&p, index - 1, ft_strlen(buf));
			// free(buf);
		}
		while (*p && *p != '>')
			p++;
		if (type == '>')
		{
			if (r_type == 2)
				fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
			else if (r_type == 1)
				fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		else
			fd = open(filename, O_RDWR, 0644);
		free_str(&filename);
		if ((!p || ft_strlen(p) == 0) && !is_next_redirect(p, type))
			return (fd);
		if (is_next_redirect(p, type))
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
	// free(tmp);
	if (!command->flags->rev_redirect)
	{
		command->fd[0] = ft_form_file(pp);
	}
	command->fd[1] = redirect(p, pp[index], index, string); //
		// fn_errors(command, errno);
	tmp = pp;
	pp = ft_strdup(*string);
	free(tmp);
}

void	validator(char **string, t_env *env, t_command *command)
{
	char	*p;
	size_t	index;
	char	quote;
	char	*tmp;

	index = 0;
	p = ft_strdup(*string); // leak
	quote = '\0';
	tmp = NULL;
	while (p[index] && ft_strlen(p))
	{
		if (p[index] == '"' || p[index] == '\'')
			p = validate_quote(&quote, p, index--);
		else if ((p[index] == '$' && (quote == 0 || quote == '"'))
		&& (p[index + 1] != ' ' || p[index+ 1] != '\0'))
			p = validate_env_sub(quote, p, index--, env);
		else if ((!ft_strncmp(&p[index], "<", 1) || !ft_strncmp(&p[index], ">", 1)) && !quote)
			redirect_logic(&p, index, command, string);
		else if (p[index] == '\\')
			p = mirroring(p, quote);
		index++;
	}
	if (quote)
		fn_errors(command, SYNTAX_ERROR);
	tmp = *string;
	*string = ft_strdup(p);
	free(p);
}
