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
	if (parsed_data == NULL)
		return 1;
	initialize_structure(parsed_data);
	parsed_data->history = (char **)malloc(sizeof(char *) * 500);
	parsed_data->raw_string = ft_strnew(0);
	if (!parsed_data || !parsed_data->raw_string || !parsed_data->history)
		return 1;
	parsed_data->env_data = parse_env(env);
	while (1)
	{
		if (flag)
		{
			parsed_data->raw_string = ft_strnew(0);
			parsed_data->option = 0;
			parsed_data->argument = 0;
			parsed_data->rest_string = 0;
		}
		write(1, "minishell> ", 11);
		tputs(save_cursor, 1, ft_putchar);
		fn_termcap(&parsed_data);
		parser(&parsed_data);
		save_history(&parsed_data);
		router(parsed_data);
		free_str(&parsed_data->raw_string);
		free_str(&parsed_data->command);
		flag = 1;
	}
	free(parsed_data->history);
	free(parsed_data->env_data);
	free(parsed_data);
}
