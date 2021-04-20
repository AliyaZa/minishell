/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 19:11:41 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:06:36 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	redir(t_command *command)
{
	char	*arg;
	int		fdout;
	int		i;
	char	*file;

	arg = ft_strdup(command->argument);
	i = 0;
	while (fn_search(arg, ">") || fn_search(arg, "<") || fn_search(arg, ">>"))
	{
		if (arg[i] == '>')
		{
			arg++;
			i++;
			while (arg == ' ')
			{
				arg++;
				i++;
			}
			file = ft_strdup(arg);
			fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		}
	}

}*/
