/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:07:01 by nhill             #+#    #+#             */
/*   Updated: 2021/04/15 17:05:46 by nhill            ###   ########.fr       */
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

static void	fn_get_name(t_env **lst_name, char *value, int flag)
{
	if ((*lst_name))
	{
		if ((*lst_name)->value != NULL)
			(*lst_name)->value = NULL;
		if ((*lst_name)->equal != NULL && (flag != 1))
			(*lst_name)->equal = NULL;
		(*lst_name)->value = ft_strdup(value);
	}
}

static void	fn_get_needed_el(char *tmp, char **value,
t_env **lst_name, t_parsed_data *parsed_data)
{
	int		len;
	char	*key;

	len = ft_strchr(tmp, '=') - tmp;
	(*value) = fn_strcreate(tmp, len + 1, ft_strlen(tmp) - len);
	key = fn_strcreate(tmp, 0, len);
	(*lst_name) = fn_get_el(parsed_data, key);
	free_str(&key);
}

static void	fn_make_part(t_parsed_data **parsed_data,
t_command *command, int *flag)
{
	char	*tmp;
	t_env	*lst;
	char	*value;
	t_env	*lst_name;

	fn_zero(&tmp, &lst, &value, &lst_name);
	if (!ft_strchr(command->argument, '='))
	{
		tmp = ft_strjoin(command->argument, "=");
		lst = fn_get_el(*parsed_data, command->argument);
		if (lst)
			lst->equal = ft_strdup("=");
		(*flag) = 1;
	}
	else
		tmp = ft_strdup(command->argument);
	fn_get_needed_el(tmp, &value, &lst_name, *parsed_data);
	if (lst_name != NULL)
		fn_get_name(&lst_name, value, *flag);
	else
		fn_set_env(*parsed_data, command, tmp, *flag);
	free_str(&tmp);
	free_str(&value);
}

void	fn_export(t_parsed_data *parsed_data, t_command *command)
{
	int		flag;

	flag = 0;
	if (command->argument[0] != '\0')
		fn_make_part(&parsed_data, command, &flag);
	else
		print_export(parsed_data->env_data);
}
