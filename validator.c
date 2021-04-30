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

#include "minishell.h"

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

	p = &(*string)[i];
	r_type = 0;
	index = 0;
	buf = NULL;
	while (p[index])
	{
		while (p[index] == ' ' || p[index] == type)
			p[index++] == type ? r_type++ : 1;
		p = ft_substr(p, index, ft_strlen(p));
		filename = ft_take_word(&p);
		if (*p == ' ')
			p++;
		buf = ft_substr(p, 0, ft_strlen_c(p, '>'));
		if (ft_strlen(buf))
		{
			*argument = ft_strjoin(*argument, buf);
			ft_delete_word(&p, index - 1, ft_strlen(buf));
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
		if ((!p || ft_strlen(p) == 0) && !is_next_redirect(p, type))
			return (fd);
		free(filename);
		if (is_next_redirect(p, type))
			close(fd);
	}
	return (fd);
}

void	validator(char **string, t_env *env, t_command *command)
{
	char	*tmp;
	char	*tmp1;
	char	*p;
	size_t	index;
	char	quote;
	char	*value;
	char	*key;
	int		kc;
	int		i;

	index = 0;
	p = ft_strdup(*string);
	quote = '\0';
	while (p[index] && ft_strlen(p))
	{
		if (p[index] == '"' || p[index] == '\'')
		{
			if (!quote || p[index] == quote)
			{
				if (!quote)
					quote = p[index];
				else if (p[index] == quote)
					quote = 0;
				tmp = ft_substr(p, 0, index);
				tmp1 = ft_substr(p, index + 1, ft_strlen(p));
				p = ft_strjoin(tmp, tmp1);
				continue ;
			}
		}
		if (p[index] == '$' && (quote == 0 || quote == '"'))
		{
			if (p[index + 1] == ' ' || p[index+ 1] == '\0')
			{
				index++;
				continue ;
			}
			tmp = ft_substr(p, 0, index);
			tmp1 = ft_substr(p, (ft_strlen_cc(&p[index], ' ', '"')) + index, ft_strlen(p));
			i = index;
			kc = 0;
			while (p[i] != ' ' && p[i] != '"' && p[i] != '\'' && p[i] != quote)
			{
				kc++;
				i++;
			}
			key = ft_substr(p, index + 1, kc - 1);
			value = get_value_by_key(env, key);
			free_str(&key);
			if (value)
				tmp = ft_strjoin_free(tmp, value, 1);
			tmp = ft_strjoin_free(tmp, tmp1, 3);
			p = tmp;
			continue ;
		}
		if ((!ft_strncmp(&p[index], "<", 1) || !ft_strncmp(&p[index], ">", 1)) && !quote)
		{
			p[index] == '<' ? command->flags->rev_redirect = 1 : 1;
			*string = ft_substr(p, 0, index);
			if (-1 == (command->fd[1] = redirect(&p, p[index], index, string)))
				fn_errors(command, 2);
			p = ft_strdup(*string);
		}
		index++;
	}
	if (quote)
		fn_errors(command, SYNTAX_ERROR);
	*string = ft_strdup(p);
	free(p);
}
