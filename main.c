/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/03/17 20:06:02 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main()
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		read(1, buf, 1);
		printf("%s\n", buf);
	}
	return (0);
}
