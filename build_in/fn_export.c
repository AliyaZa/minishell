/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:07:01 by nhill             #+#    #+#             */
/*   Updated: 2021/04/12 16:33:11 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_env *parsed_data)
{
	int		i;
	t_env	*parsed_data1;

	i = 0;
	parsed_data1 = parsed_data;
	while (parsed_data1 != NULL)
	{
		if (!parsed_data1->equal)
			printf("declare -x %s=\"%s\"\n",
				parsed_data1->key, parsed_data1->value);
		else
			printf("declare -x %s\n", parsed_data1->key);
		parsed_data1 = parsed_data1->next;
	}
}

static void	fn_get_name(t_env **lst_name, char *value)
{
	if ((*lst_name))
	{
		free_str((*lst_name)->value);
		(*lst_name)->value = ft_strdup(value);
	}
}

void	fn_export(t_parsed_data *parsed_data, t_command *command)
{
	char	*tmp;
	t_env	*lst_name;
	char	*value;

	lst_name = NULL;
	tmp = NULL;
	value = NULL;
	if (command->argument[0] != '\0')
	{
		if (!ft_strchr(command->argument, '='))
		{
			tmp = ft_strjoin(command->argument, "=");
			fn_get_el(parsed_data, command->argument)->equal = ft_strdup("=");
		}
		else
			tmp = ft_strdup(command->argument);
		value = fn_strcreate(tmp, 0, (ft_strchr(tmp, '=') - tmp));
		lst_name = fn_get_el(parsed_data, value);
		fn_get_name(&lst_name, value);
		fn_set_env(parsed_data, tmp);
	}
	else
		print_export(parsed_data->env_data);
	free_str(&tmp);
	free_str(&value);
}
