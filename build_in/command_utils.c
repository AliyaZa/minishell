/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:51:26 by nhill             #+#    #+#             */
/*   Updated: 2021/04/12 19:17:56 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*fn_create_el(char *tmp)
{
	t_env	*new_el;
	int		len;

	new_el = malloc(sizeof(t_env));
	len = ft_strchr(tmp, '=') - tmp;
	new_el->key = fn_strcreate(tmp, 0, len);
	if ((ft_strlen(tmp) - len) > 0)
		new_el->value = fn_strcreate(tmp, len + 1, ft_strlen(tmp) - len);
	else
		new_el->value = NULL;
	new_el->next = NULL;
	return (new_el);
}

char	*fn_strcreate(char *s, int start, int len)
{
	char	*str;
	char	*tmp;

	str = NULL;
	if (s)
	{
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (str)
		{
			tmp = str;
			while (*(s + start) && len--)
			{
				*tmp++ = *(s + start);
				start++;
			}
		}
	}
	return (str);
}

char	*fn_strjoin3(char *str1, char *str2, char *str3)
{
	char	*str;
	size_t	size;

	if (ft_strcmp(str1, "/"))
		size = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	else
		size = ft_strlen(str2) + ft_strlen(str3);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	else
		ft_bzero(str, size + 1);
	if (ft_strcmp(str1, "/"))
		str = ft_strcpy(str, str1);
	str = ft_strlcat(str, str2);
	str = ft_strlcat(str, str3);
	return (str);
}

static int	fn_creator(t_env **env_copy, char **value, char *tmp)
{
	int		flag;

	flag = 0;
	while ((*env_copy) && !fn_search((*env_copy)->value, *value))
	{
		(*env_copy) = (*env_copy)->next;
	}
	free(*value);
	*value = NULL;
	if (env_copy)
	{
		free((*env_copy)->value);
		(*env_copy)->value = ft_strdup(
				(&(tmp[ft_strlen((*env_copy)->key) + 1])));
		flag = 1;
	}
	return (flag);
}

void	fn_set_env(t_parsed_data *parsed_data, t_command *command, char *tmp)
{
	t_env	*env;
	char	*value;
	t_env	*env_copy;
	int		flag;

	env = NULL;
	env_copy = parsed_data->env_data;
	value = NULL;
	if (ft_strchr(tmp, '='))
	{
		value = fn_strcreate(tmp, 0, (ft_strchr(tmp, '=') - tmp));
		flag = fn_creator(&env_copy, &value, tmp);
		if (flag == 0)
		{
			env = fn_create_el(tmp);
			ft_lstadd_back2(&parsed_data->env_data, env);
		}
	}
	else
		fn_errors(command, errno);
}
