/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:59:28 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 17:40:22 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
