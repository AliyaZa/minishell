/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:07:01 by nhill             #+#    #+#             */
/*   Updated: 2021/04/08 20:38:36 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_parsed_data *parsed_data)
{
	int		i;

	i = 0;
	while (parsed_data->env_data != NULL)
	{
		if (!parsed_data->env_data->equal)
			printf("declare -x %s=\"%s\"\n", parsed_data->env_data->key, parsed_data->env_data->value);
		else
			printf("declare -x %s\n", parsed_data->env_data->key);
		parsed_data->env_data = parsed_data->env_data->next;
	}
}

void	fn_export(t_parsed_data *parsed_data, t_command *command)
{
	char	*tmp;

	if (command->argument[0] != '\0')
	{
		if (!ft_strchr(command->argument, '='))
		{
			tmp = ft_strjoin(command->argument, "=");
			fn_set_env(parsed_data, tmp);
			fn_get_el(parsed_data, command->argument)->equal = ft_strdup("=");
		}
		else
			fn_set_env(parsed_data, command->argument);
	}
	else
	{
		print_export(parsed_data);
	}
}
