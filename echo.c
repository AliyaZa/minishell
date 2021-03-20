/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:59:28 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 17:27:40 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			fn_search(char *s1, char *s2)
{
	if (s1 && s2)
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (1);
	}
	return (0);
}

void		fn_echo(char	*parsed_data)
{
	int		index;
	int		flag;

	index = 0;
	while (parsed_data[index])
	{
		if (fn_search(&parsed_data[index], "-n"))
			flag = 1;
		else
			printf("%c", parsed_data[index]);
		index++;
	}
	if (flag)
		printf("\n");
}
