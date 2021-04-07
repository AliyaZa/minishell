/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/04/05 18:46:03 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	struct	termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
	if ((main_cycle(env)) == 1)
		write(1, "error\n", 6);
	printf("first argument - %s\nargc - %d env[1] - %s\n", argv[0], argc, env[1]);
	return (0);
}
