/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:07:14 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 20:07:19 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env_data, t_command *command)
{
	size_t	i;

	i = 0;
	while (env_data != NULL)
	{
		if (!env_data->equal)
		{
			ft_putstr_fd(env_data->key, command->fd[1]);
			ft_putstr_fd("=", command->fd[1]);
			ft_putstr_fd(env_data->value, command->fd[1]);
			ft_putstr_fd("\n", command->fd[1]);
		}
		env_data = env_data->next;
	}
}
