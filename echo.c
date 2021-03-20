/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:59:28 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 17:47:45 by nhill            ###   ########.fr       */
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

void        fn_echo(char    *parsed_data)
{
    int        flag;

    flag = 0;
   // parsed_data++;
    if (fn_search(" -n" ,parsed_data))
    {
        parsed_data += 4;
        flag = 1;
    }
    printf("%s", parsed_data);
    if (flag)
        printf("\n");
}
