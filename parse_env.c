/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:36:22 by mismene           #+#    #+#             */
/*   Updated: 2021/04/24 16:53:33 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parse_env(char **env)
{
	t_env	*env_el;
	char	**matrix;
	t_env	*our_env;
	size_t	i;

	i = 0;
	our_env = NULL;
	while (env[i])
	{
		env_el = malloc(sizeof(t_env));
		env_el->next =NULL;
		matrix = ft_split(env[i], '=');
		env_el->key = ft_strdup(matrix[0]);
		env_el->value = ft_strdup(matrix[1]);
		env_el->equal = NULL;
		env_el->order = i;
		ft_lstadd_back2(&our_env, env_el);
		free(matrix[0]);
		free(matrix[1]);
		free(matrix);
		i++;
	}
	return (our_env);
}

