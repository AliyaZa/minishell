/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:49 by mismene           #+#    #+#             */
/*   Updated: 2021/04/05 18:58:52 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_cycle(char **env)
{
	t_parsed_data	*parsed_data;
	size_t			flag;

	flag = 0;
	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	initialize_structure(parsed_data);
	parsed_data->history = (char **)malloc(sizeof(char *) * 500);
	parsed_data->raw_string = ft_strnew(1);
	if (!parsed_data || !parsed_data->raw_string || !parsed_data->history)
		return 1;
	parsed_data->env_data = parse_env(env);
	while (1)
	{
		if (flag)
			initialize_structure(parsed_data);
		write(1, "minishell> ", 11);
		fn_termcap(&parsed_data);
		parser(&parsed_data);
		// save_history(&parsed_data);
		router(parsed_data);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
		flag = 1;
	}
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
}
