/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:30:37 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:25:13 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rez;
	size_t	i;
	size_t	l;

	i = 0;
	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	rez = (char *)malloc((l + 1) * sizeof(char));
	if (!rez)
		return (NULL);
	while (i < l)
	{
		rez[i] = f(i, s[i]);
		i++;
	}
	rez[i] = '\0';
	return (rez);
}
