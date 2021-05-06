/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:19:54 by nhill             #+#    #+#             */
/*   Updated: 2021/05/06 21:34:22 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_count_lst(t_env *env)
{
	int		count;

	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

char	*create_str_ex(char *str)
{
	char		*rez;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 1;
	j = 0;
	len = ft_strlen(str);
	rez = (char *)malloc(sizeof(char) * (len + 3));
	rez[0] = '"';
	while (j < len)
	{
		rez[i++] = str[j++];
	}
	rez[i++] = '"';
	rez[i] = '\0';
	return (rez);
}

char	**fn_arr(t_env *env)
{
	int		kol;
	char	**res;
	int		i;

	kol = ft_count_lst(env);
	res = (char **)malloc(sizeof(char *) * (kol + 1));
	ft_bzero(res, sizeof(char *) * (kol + 1));
	i = 0;
	while (env)
	{
		if (env->equal == NULL)
			res[i++] = fn_strjoin3(env->key, "=", env->value);
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}

void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		signal(SIGINT, proc_signal_handler);
	}
}
