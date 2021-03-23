/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:59:28 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 18:43:42 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        fn_echo(char    *output)
{
    int        flag;

    flag = 0;
   // parsed_data++;
    if (fn_search(" -n" ,output))
    {
        output += 4;
        flag = 1;
    }
    printf("%s", output);
    if (flag)
        printf("\n");
}
