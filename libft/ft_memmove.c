/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:19:18 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:56:31 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char	*b;
	unsigned char	*a;
	size_t			i;

	a = (unsigned char *)destination;
	b = (unsigned char *)source;
	i = 0;
	if (destination == NULL && source == NULL)
		return (NULL);
	i = n;
	if (a > b)
	{
		while (i > 0)
		{
			i--;
			a[i] = b[i];
		}
	}
	else
	{
		i = 0;
		ft_memcpy(a, b, n);
	}
	return (destination);
}
