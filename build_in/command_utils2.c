/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:21:20 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 20:09:32 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		fn_zero(char **tmp, t_env **lst, char **value, t_env **lst_name)
{
	(*tmp) = NULL;
	(*lst) = NULL;
	(*value) = NULL;
	(*lst_name) = NULL;
}

int			fn_check(char *new_path, t_command *command)
{
	struct stat	fl;

	if (stat(new_path, &fl))
		return (fn_errors(command, errno));
	if (!S_ISDIR(fl.st_mode))
		return (fn_errors(command, IS_FILE));
	if (access(new_path, X_OK))
		return (fn_errors(command, errno));
	return (1);
}

t_env		*create_export(t_parsed_data *parsed_data)
{
	t_env		*copy_env;
	t_env		*export;
	t_env		*export_el;

	copy_env = parsed_data->env_data;
	export = NULL;
	while (copy_env)
	{
		export_el = malloc(sizeof(t_env));
		export_el->next = NULL;
		export_el->key = ft_strdup(copy_env->key);
		export_el->value = ft_strdup(copy_env->value);
		export_el->equal = ft_strdup(copy_env->equal);
		export_el->order = copy_env->order;
		ft_lstadd_back2(&export, export_el);
		copy_env = copy_env->next;
	}
	return (export);
}

void		fn_get_name(t_env **lst_name, char *value, int flag)
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

void		fn_get_needed_el(char *tmp, char **value,
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
