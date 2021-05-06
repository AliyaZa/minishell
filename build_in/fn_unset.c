/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:38:20 by nhill             #+#    #+#             */
/*   Updated: 2021/04/12 16:26:07 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fn_del_el(t_env **root)
{
	if ((*root)->key)
	{
		free((*root)->key);
		(*root)->key = NULL;
	}
	if ((*root)->value)
	{
		free((*root)->value);
		(*root)->value = NULL;
	}
}

void		fn_unset(t_parsed_data *parsed_data, t_command *command)
{
	t_env	*prev;
	t_env	*root;

	root = parsed_data->env_data;
	if (fn_search(parsed_data->env_data->key, command->argument))
		parsed_data->env_data = parsed_data->env_data->next;
	else
	{
		while (root->next)
		{
			prev = root;
			root = root->next;
			if (fn_search(root->key, command->argument))
			{
				prev->next = root->next;
				fn_del_el(&root);
				if (root)
					free(root);
				root = NULL;
				break ;
			}
		}
	}
	root = parsed_data->env_data;
}
