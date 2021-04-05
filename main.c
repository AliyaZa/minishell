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
	int		l;
	char	str[2000];
	struct	termios term;
	char	*terminal_name = "xterm-256color";

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, terminal_name);

	while (ft_strncmp(str, "\n", 1))
	{
		l = read(0, str, 100);
		if (!ft_strncmp(str, "\e[A", 3))
		{
			write(1, "prev\n", 5);
		}
		else if (!ft_strncmp(str, "\e[B", 3))
		{
			write(1, "next\n", 5);
		}
		else if (!ft_strncmp(str, "\e[D", 3))
		{
			write(1, "left\n", 5);
		}
		else if (!ft_strncmp(str, "\e[C", 3))
		{
			write(1, "right\n", 6);
		}
		else
		{
			write(1, str, l);
		}
	}


	// main_cycle(env);
	printf("first argument - %s\nargc - %d env[1] - %s\n", argv[0], argc, env[1]);
	return (0);
}
