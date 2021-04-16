/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:47:10 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:56:00 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*src;
	int				i;

	i = 0;
	src = (unsigned char *)dest;
	while (n > 0)
	{
		src[i] = (unsigned char)c;
		i++;
		n--;
	}
	return (dest);
}
