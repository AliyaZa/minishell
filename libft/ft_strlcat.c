/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:28:58 by nhill             #+#    #+#             */
/*   Updated: 2021/03/22 16:12:42 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlcat(char *dst, const char *src)
{
	size_t	i;
	size_t	lens;
	size_t	lend;

	i = 0;
	lens = 0;
	while (dst[i])
		i++;
	lend = i;
	while (src[lens])
		dst[i++] = src[lens++];
	dst[i] = '\0';
	return (dst);
}
