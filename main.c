/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 16:19:36 by mismene          ###   ########.fr       */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	main_cycle(env);
	printf("first argument - %s\nargc - %d env[1] - %s\n", argv[0], argc, env[1]);
	return (0);
}
