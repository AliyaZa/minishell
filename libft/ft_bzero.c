/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:35:27 by nhill             #+#    #+#             */
/*   Updated: 2020/11/06 16:52:20 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*src;
	int				i;

	i = 0;
	src = (unsigned char*)s;
	while (n > 0)
	{
		src[i] = '\0';
		i++;
		n--;
	}
}
