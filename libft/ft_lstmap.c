/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:26:59 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 18:00:24 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*fir;

	if (!lst || !f)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (NULL);
	fir = res;
	while (lst->next)
	{
		lst = lst->next;
		res->next = ft_lstnew(f(lst->content));
		if (!res->next)
		{
			ft_lstclear(&fir, del);
			return (NULL);
		}
		res = res->next;
	}
	return (fir);
}
