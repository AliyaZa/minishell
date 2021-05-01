/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_part_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:45:40 by mismene           #+#    #+#             */
/*   Updated: 2021/04/27 14:45:43 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_command(char **command)
{
	size_t	index;
	char	*p;
	char	*start;
	char	*end;
	char	flag;

	p = ft_strdup(*command);
	index = 0;
	flag = 0;
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
		{
			if (!flag)
				flag = p[index];
			else if (flag == p[index])
				flag = 0;
			start = ft_substr(p, 0, index);
			end = ft_substr(p, index + 1, ft_strlen(p));
			p = ft_strjoin(start, end);
			continue ;
		}
		index++;
	}
	if (flag)
		return (1);
	*command = ft_strdup(p);
	return (0);
}

char	*validate_raw_string(char *raw_string)
{
	char	*p;
	size_t	index;
	char	quote;

	index = 0;
	p = ft_strdup(raw_string);
	free(raw_string);
	quote = '\0';
	while (p[index])
	{
		if (p[index] == '\'' || p[index] == '"')
		{
			if (p[index] == quote)
				quote = '\0';
			else if (!quote)
				quote = p[index];
		}
		if (quote && p[index] == ' ')
		{
			p[index] = -1;
		}
		index++;
	}
	return (p);
}

int		ft_form_file(char *file)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = 0;
	while (file[i] && (file[i] != ' ' && file[i] != '>' && file[i] != '<'))
		i++;
	fd = open(ft_substr(file, 0, i), O_RDWR, 0644);
	return (fd);
}