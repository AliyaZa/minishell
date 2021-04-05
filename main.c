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

	// return termcap_test(argc, argv);

	main_cycle(env);
	printf("first argument - %s\nargc - %d\n", argv[0], argc);

	int		l;
	char	str[2000];
	struct	termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	l = read(0, str, 100);
	write(1, str, l);
	write(1, "\n", 1);
	// main_cycle(env);
	printf("first argument - %s\nargc - %d env[1] - %s\n", argv[0], argc, env[1]);
	return (0);
}
