/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:21:20 by nhill             #+#    #+#             */
/*   Updated: 2021/04/15 17:58:25 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fn_zero(char **tmp, t_env **lst, char **value, t_env **lst_name)
{
	(*tmp) = NULL;
	(*lst) = NULL;
	(*value) = NULL;
	(*lst_name) = NULL;
}

int		fn_check(char *new_path, t_command *command)
{
	struct stat	fl;

	if (stat(new_path, &fl))
		return (fn_errors(command, errno));
	if (!S_ISDIR(fl.st_mode))
		return (fn_errors(command,IS_FILE));
	if (accessn(new_path, X_OK))
		return (fn_errors(command, errno));
	return (1);
}
