/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 14:10:09 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser allocate memory, free it after usage
int		main(int argc, char **argv, char **env)
{
	printf("%s %d\n", argv[0], argc);
	t_parsed_data	*parsed_data;
	int t;
	for(t=0; env[t]; t++)
		printf("%s\n", env[t]);
	parsed_data = parser();
	return (0);
}
