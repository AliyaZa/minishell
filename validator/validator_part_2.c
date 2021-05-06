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

#include "../minishell.h"

int		validate_command(char **command)
{
	size_t	index;
	char	*p;
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
			ft_delete_char(&p, index);
			continue ;
		}
		index++;
	}
	if (flag)
		return (1);
	free_four(command, &p, NULL, NULL);
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
	char	*filename;

	i = 0;
	fd = 0;
	while (file[i] && (file[i] != ' ' && file[i] != '>' && file[i] != '<'))
		i++;
	filename = ft_substr(file, 0, i);
	fd = open(filename, O_RDWR, 0644);
	free(filename);
	return (fd);
}

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
