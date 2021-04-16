/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:04:47 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:19:21 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*prev;
	t_list	*ls;

	if (!lst)
		return ;
	ls = *lst;
	if (!ls)
		return ;
	while (ls->next)
	{
		prev = ls;
		ls = ls->next;
		if (del)
			del(prev->content);
		free(prev);
	}
	if (del)
		del(ls->content);
	free(ls);
	*lst = NULL;
}
