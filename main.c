/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/04/15 18:15:44 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	errno = 0;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: Too many arguments\n", 2);
		return (0);
	}
	term_ini();
	if ((main_cycle(env)) == 1)
		ft_putstr_fd("error during memory allocation!\n", 1);
	(void)argv[0][0];
	return (0);
}
