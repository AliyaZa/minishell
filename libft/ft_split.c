/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:20:54 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:54:07 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_str(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (s[0] != c)
		count++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i])
				count++;
		}
		if (s[i])
			i++;
	}
	return (count);
}

static int	ft_count_len(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_clean(char **arr, int c1)
{
	int		i;

	if (arr)
	{
		i = 0;
		while (i < c1)
			if (arr[i])
				free(arr[i++]);
		free(arr);
	}
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		count[2];
	int		j;

	i = 0;
	if (!s)
		return (0);
	count[0] = ft_count_str(s, c);
	ptr = (char **)malloc((count[0] + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	while (i < count[0] && *s)
	{
		while (*s == c)
			s++;
		count[1] = ft_count_len(s, c);
		ptr[i] = (char *)malloc((count[1] + 1) * sizeof(char));
		if (!ptr[i])
			return (ft_clean(ptr, i));
		j = 0;
		while (j < count[1] && *s)
			ptr[i][j++] = *(s++);
		ptr[i++][j] = '\0';
	}
	ptr[i] = 0;
	return (ptr);
}
