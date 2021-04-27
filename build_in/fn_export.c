/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:07:01 by nhill             #+#    #+#             */
/*   Updated: 2021/04/27 20:29:40 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**create_sort_export(t_env *parsed_data)
{
	int		i;
	t_env	*parsed_data1;
	char	**tmp;

	i = 0;
	parsed_data1 = parsed_data;
	tmp = (char**)ft_calloc(ft_lstsize1(parsed_data1), sizeof(char *));
	while (parsed_data1 != NULL)
	{
		if (!parsed_data1->equal)
			tmp[i] = fn_strjoin3(fn_strjoin3("declare -x ", parsed_data1->key, "="), parsed_data1->value, "\n");
//			printf("declare -x %s=\"%s\"\n",
//				parsed_data1->key, parsed_data1->value);
		else
			tmp[i] = fn_strjoin3("declare -x ", parsed_data1->key, "\n");
//			printf("declare -x %s\n", parsed_data1->key);
		i++;
		parsed_data1 = parsed_data1->next;
	}
	return (tmp);
}

static char		**sort_tmp(char **tmp, t_env *parsed_data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while(i < ft_lstsize1(parsed_data) - 1)
	{
		j = 0;
		while (j < ft_lstsize1(parsed_data) - i - 1)
		{
			if(ft_strcmp(tmp[j], tmp[j + 1]) > 0)
			{
				str = ft_strdup(tmp[j]);
				free_str(&tmp[j]);
				tmp[j] = strdup(tmp[j + 1]);
				free_str(&tmp[j + 1]);
				tmp[j + 1] = ft_strdup(str);
			}
			j++;
		}
		i++;
	}
	return(tmp);
}

static void		print_export(t_env *parsed_data, t_command *command)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = create_sort_export(parsed_data);
	tmp = sort_tmp(tmp ,parsed_data);
	while (i < ft_lstsize1(parsed_data))
	{
		ft_putstr_fd(tmp[i], command->fd[1]);
		i++;
	}
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
		print_export(parsed_data->env_data, command);
}
