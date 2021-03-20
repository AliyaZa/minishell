/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 16:38:56 by mismene          ###   ########.fr       */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser allocate memory, free it after usage
int		main(int argc, char **argv, char **env)
{
	t_parsed_data	*parsed_data;
	t_env			*env_data;

	env_data = parse_env(env);
	parsed_data = parser();
	for (; env_data->next!=0; env_data = env_data->next)
	{
		printf("%s=%s\n", env_data->key, env_data->value);
	}
	printf("%s %d\n", argv[0], argc);
	return (0);
}
