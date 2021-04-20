/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:49:51 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:24:44 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int		i;

	i = 0;
	if (str1 && str2)
	{
		while (str2[i] && str1[i])
		{
			if ((unsigned char)str2[i] == (unsigned char)str1[i])
				i++;
			else
				return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
