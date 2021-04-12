/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:48:51 by nhill             #+#    #+#             */
/*   Updated: 2021/04/08 20:34:16 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			i++;
	return (i);
}

size_t	ft_strlen_c(const char *s, const char c)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] != c && s[i] != '\0')
			i++;
	return (i);
}

