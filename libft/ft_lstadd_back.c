/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:40:52 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 15:43:01 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ls;

	if (!new)
		return ;
	ls = *lst;
	if (!ls)
		*lst = new;
	else
	{
		while (ls->next)
			ls = ls->next;
		ls->next = new;
	}
}

void	ft_lstadd_back2(t_env **env, t_env *new)
{
	t_env	*ls;

	if (!new)
		return ;
	ls = *env;
	if (!ls)
		*env = new;
	else
	{
		while (ls->next)
			ls = ls->next;
		ls->next = new;
	}
}
