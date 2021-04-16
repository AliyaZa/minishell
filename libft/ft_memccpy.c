/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:01:53 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:57:53 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char	*b;
	unsigned char	*a;
	int				i;

	a = (unsigned char *)destination;
	b = (unsigned char *)source;
	i = 0;
	while (n > 0)
	{
		a[i] = b[i];
		if ((unsigned char)c == b[i])
			return (&a[++i]);
		i++;
		n--;
	}
	return (NULL);
}
