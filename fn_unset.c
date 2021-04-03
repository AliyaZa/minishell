/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:38:20 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 17:00:15 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2/minishell.h"

void		fn_del_el(t_env **root)
{
	if((*root)->key)
	{
		free((*root)->key);
		(*root)->key = NULL;
	}
	if((*root)->value)
	{
		free((*root)->value);
		(*root)->value = NULL;
	}
}

void		fn_unset(t_env **our_env, char *history)
{
	t_env	env;
	t_env	*prev;
	t_env	*root;

	//env = 0;
	root = *our_env;
	if (fn_search((*our_env)->key, history))
		*our_env = (*our_env)->next;
	else
	{
		while (root->next)
		{
			prev = root;
			root = root->next;
			if (fn_search(root->key, history))
			{
				prev->next = root->next;
				fn_del_el(&root);
				if (root)
					free(root);
				root = NULL;
				break;
			}
		}
	}
	root = *our_env;
}
