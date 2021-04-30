/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:04:30 by nhill             #+#    #+#             */
/*   Updated: 2021/04/30 19:27:52 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		kol_pipe(char **arr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][j])
		{
			j++;
		}
		i++;
	}
	return(i);
}


//форк перепиши

void	fn_pipes(t_parsed_data *parsed_data ,t_command *command, int kol)
{
	int		i;
	int		fd[kol][2];

	i = 0;
	while (i++ < kol)
	{
		pipe(command->fd[i]);
	}
	i = 0;
	while (command->pipes)
	{
		if (fork() == 0)
			fn_fork(parsed_data, command);
	}
}*/
