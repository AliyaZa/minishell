/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:59:45 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:36:18 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = NULL;
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(s1))
			+ (ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

static void	for_norm(int flag, char **s1, char **s2)
{
	if (flag == 1)
		free(*s1);
	else if (flag == 2)
		free(*s2);
	else if (flag == 3)
	{
		free(*s1);
		free(*s2);
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		++i;
		++j;
	}
	for_norm(flag, &s1, &s2);
	p[i] = '\0';
	return (p);
}
