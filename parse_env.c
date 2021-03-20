/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:36:22 by mismene           #+#    #+#             */
/*   Updated: 2021/03/20 16:36:47 by mismene          ###   ########.fr       */
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
		ft_lstadd_back(&our_env, env_el);
		free(matrix[0]);
		free(matrix[1]);
		free(matrix);
		i++;
	}
	return (our_env);
}
