/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:54:53 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:26:53 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup_c(const char *str, char c)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i] != c)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
