/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:38:31 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:57:08 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)arr;
	while (n > 0)
	{
		if (*a == (unsigned char)c)
			return (a);
		n--;
		a++;
	}
	return (NULL);
}
