/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:01:33 by mismene           #+#    #+#             */
/*   Updated: 2021/04/20 15:06:43 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_command *command)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	write(command->fd[1], pwd, ft_strlen(pwd));
	write(command->fd[1], "\n", 1);
}
