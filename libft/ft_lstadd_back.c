/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:40:52 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 15:19:56 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*ls;

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
