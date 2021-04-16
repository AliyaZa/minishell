/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:50:29 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:56:44 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char	*b;
	unsigned char	*a;
	int				i;

	a = (unsigned char *)destination;
	b = (unsigned char *)source;
	i = 0;
	if (a == NULL && b == NULL)
		return (NULL);
	while (n > 0)
	{
		a[i] = b[i];
		i++;
		n--;
	}
	return (destination);
}
