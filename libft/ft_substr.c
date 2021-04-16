/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:44:21 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:22:23 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	j;

	if (s)
		j = ft_strlen(s);
	else
		j = 0;
	if (j < start)
		len = 0;
	if (len > j - start)
		len = j - start;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	s += start;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*str;
	char	*st;

	if (s == NULL || (len + 1 == 0))
		return (NULL);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (*s && start--)
		s++;
	st = str;
	while (len-- && *s)
		*str++ = *s++;
	*str = '\0';
	free(s);
	return (st);
}
