/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:33:12 by nhill             #+#    #+#             */
/*   Updated: 2021/04/16 17:55:25 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(long n, int fd)
{
	char		c;

	if (n > 9)
		ft_putnbr(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	long	nn;

	nn = n;
	if (n < 0)
	{
		nn = -nn;
		write(fd, "-", 1);
	}
	ft_putnbr(nn, fd);
}
