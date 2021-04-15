/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 19:11:41 by nhill             #+#    #+#             */
/*   Updated: 2021/04/15 19:27:23 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir(t_command *command)
{
	char *arg;

	arg = command->argument;
	while (fn_search(arg, ">") || fn_search(arg, "<") || fn_search(arg, ">>"))
	{

	}

}
