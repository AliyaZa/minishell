/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:04:00 by mismene           #+#    #+#             */
/*   Updated: 2021/04/20 16:36:21 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_next_redirect(char *string)
{
	int		index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '>')
			return (1);
		else if (string[index] == '"' || string[index] == '\'')
			return (0);
		index++;
	}
	return (0);
}

int		redirect(char *string)
{
	int		fd;
	char	*filename;
	size_t	index;
	char	*tmp;
	int		r_type;

	r_type = 0;
	index = 0;
	while (string[index])
	{
		tmp = string;
		while (string[index] == ' ' || string[index] == '>')
			string[index++] == '>' ? r_type++ : 1;
		string = ft_substr(string, index, ft_strlen(string));
		filename = ft_take_word(&string);
		if (r_type == 2)
			fd = open(filename, O_RDWR | O_CREAT, 0777);
		else if (r_type == 1)
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if ((!string || ft_strlen(string) == 0) && !is_next_redirect(string))
		{
			return (fd);
		}
		free(filename);
		free(tmp);
		if (is_next_redirect(string))
		{
			close(fd);
		}
	}
	return (fd);
}

void	validator(char **string, t_env *env, t_command *command)
{
	char	*tmp;
	char	*tmp1;
	char	*p;
	int		index;
	char	flag;
	char	*value;
	char	*key;
	int		kc;
	int		i;

	index = 0;
	p = ft_strdup(*string);
	(void)(env->key);
	(void)(command->command);
	flag = 0;
	while (p[index])
	{
		if (p[index] == '"' || p[index] == '\'')
		{
			if (!flag || p[index] == flag)
			{
				if (!flag)
					flag = p[index];
				else if (p[index] == flag)
					flag = 0;
				tmp = ft_substr(p, 0, index);
				tmp1 = ft_substr(p, index + 1, ft_strlen(p));
				p = ft_strjoin(tmp, tmp1);
				continue ;
			}
		}
		if (p[index] == '$' && (flag == 0 || flag == '"'))
		{
			tmp = ft_substr(p, 0, index);
			tmp1 = ft_substr(p, (ft_strlen_c(&p[index], ' ')) + index, ft_strlen(p));
			i = index;
			kc = 0;
			while (p[i] != ' ' && p[i] != flag)
			{
				kc++;
				i++;
			}
			key = ft_substr(p, index +1, kc - 1);
			value = get_value_by_key(env, key);
			free(key);
			if (value)
			{
				tmp = ft_strjoin_free(tmp, value, 1);
			}
			tmp = ft_strjoin_free(tmp, tmp1, 3);
			p = tmp;
			continue ;
		}
		if (!ft_strncmp(&p[index], ">", 1) && !flag)
		{
			// char	*text = ft_substr(p, 0, index);
			command->fd = redirect(ft_substr(&p[index], 0 , ft_strlen(&p[index])));
		}
		index++;
	}
	*string = ft_strdup(p);
	free(p);
}
