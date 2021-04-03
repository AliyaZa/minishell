/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:07:01 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 16:20:25 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2/minishell.h"

void	fn_export(t_env **our_env, char **history, int i)
{
	fn_set_env(our_env, history, i);
}
