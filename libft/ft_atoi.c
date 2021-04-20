/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:31:43 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 18:02:37 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c && ((c == 32) || ((c >= 9) && (c <= 13))))
		return (1);
	return (0);
}

static void	for_norm(const char *str, int *i, int *zn)
{
	if ((str[*i] == '+') || (str[*i] == '-'))
	{
		if (str[*i] == '-')
			(*zn) = -(*zn);
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	unsigned int	ch;
	unsigned int	l_ch;
	int				i;
	int				zn;

	ch = 0;
	i = 0;
	zn = 1;
	while (str[i] && (ft_isspace(str[i])))
		i++;
	for_norm(str, &i, &zn);
	while (str[i] >= '0' && str[i] <= '9')
	{
		l_ch = ch;
		ch = ch * 10 + (unsigned int)(str[i++] - '0');
		if (l_ch > ch)
		{
			if (zn > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (ch * zn);
}
