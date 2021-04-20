/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:04:00 by mismene           #+#    #+#             */
/*   Updated: 2021/03/19 14:45:58 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirect(char *text, char *string)
{
	int		fd;
	char	*filename;
	size_t	index;
	char	*tmp;

	index = 0;
	tmp = string;
	filename = ft_take_word(&string);
	while (string[index] == ' ' || string[index] == '>')
		index++;
	string = ft_substr(string, index, ft_strlen(string));
	free(tmp);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (!string || ft_strlen(string) == 0)
		return (fd);
	close(fd);
	redirect(text, string);
	return (0);
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
		if (!ft_strncmp(&p[index], ">>", 2) && !flag)
		{
			char	*text = ft_substr(p, 0, index);
			index += 2;
			command->fd = redirect(text, ft_substr(&p[index], 0 , ft_strlen(&p[index])));
		}
		index++;
	}
	*string = ft_strdup(p);
	free(p);
}
