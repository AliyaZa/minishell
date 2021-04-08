/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:35:24 by nhill             #+#    #+#             */
/*   Updated: 2021/04/07 18:26:48 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env		*fn_get_el(t_parsed_data *parsed_data, char *key)
{
	t_env	*tmp;

	tmp = parsed_data->env_data;
	while (tmp && !(fn_search(tmp->key, key)))
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

static char		*fn_strjoin3(char *str1, char *str2, char *str3)
{
	char	*str;
	size_t	size;
	if (ft_strcmp(str1, "/"))
		size = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	else
		size = ft_strlen(str2) + ft_strlen(str3);
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return(NULL);
	else
		ft_bzero(str,size + 1);
	if (ft_strcmp(str1, "/"))
		str = ft_strcpy(str, str1);
	str = ft_strlcat(str, str2);
	str = ft_strlcat(str, str3);
	return(str);
}

static char	*fn_new_path(t_parsed_data *parsed_data, t_env *home)
{
	char	*path;
	char	*new_path;

	path = NULL;
	new_path = NULL;
	path = getcwd(path, PATH_MAX);
	if (parsed_data->argument)
		new_path = fn_strjoin3(path, "/", parsed_data->argument);
	else
		new_path = ft_strdup(home->value);
	free(path);
	path = NULL;
	return (new_path);
}

static char	*fn_get_path(t_parsed_data *parsed_data)
{
	char	*new_path;
	t_env	*home;
	t_env	*tmp;

	new_path = NULL;
	home = NULL;
	tmp = NULL;
	if ((!(home = fn_get_el(parsed_data, "HOME")) && !(parsed_data->command)) ||
		fn_search(parsed_data->rest_string, "~"))
		return (NULL);
	else if (parsed_data->rest_string && parsed_data->rest_string[0] == '/')
		new_path = ft_strdup(parsed_data->rest_string);
	else if (fn_search(parsed_data->rest_string, "-"))
	{
		if (!fn_get_el(parsed_data->env_data->key, "OLDPWD"))
			return (NULL);
		else
		{
			tmp = fn_get_el(parsed_data, "OLDPWD");
			new_path = ft_strdup(tmp->value);
		}
	}
	else
		new_path = fn_new_path(parsed_data, home);
	return (new_path);
}

static char	*fn_strcreate(char *s, int start, char c)
{
	char	*str;
	char	*tmp;
	int		len;

	str = NULL;
	len = ft_strchr(s, c) - s;
	if (s)
	{
		if ((str = (char *)malloc(sizeof(char) * (len + 1))))
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

static t_env	*fn_create_el(char *tmp)
{
	t_env	*new_el;
	int		len;

	new_el = malloc(sizeof(t_env));
	len = ft_strchr(tmp, '=') - tmp;
	new_el->key = fn_strcreate(tmp, 0, len);
	new_el->value = fn_strcreate(tmp, len + 1, ft_strlen(tmp) - len);
	new_el->next = NULL;
	return (new_el);
}

static void	fn_set_env(t_parsed_data *parsed_data, char *tmp)
{
	t_env	*env;
	char	*value;
	t_env	*env_copy;

	env = NULL;
	env_copy = parsed_data->env_data;
	value = NULL;
	if (ft_strchr(tmp, '='))
	{
		value = fn_strcreate(tmp, 0, '=');
		while (env_copy && !fn_search(env_copy->value, value))
		{
			env_copy = env_copy->next;
		}
		free(value);
		if (env_copy)
		{
			free(env_copy->value);
			env_copy->value = ft_strdup((&(tmp[ft_strlen(env_copy->key) + 1])));
		}
		else
		{
			env = fn_create_el(tmp);
			ft_lstadd_back2(&parsed_data->env_data, env);
		}
	}
	else
		return ;
}

static void	fn_change_cd(t_parsed_data *parsed_data, char *path, char *env_key)
{
	t_env	*lst_name;
	char	*tmp;

	lst_name = NULL;
	tmp = NULL;
	if ((lst_name = fn_get_el(parsed_data, env_key)))
	{
		free(lst_name->value);
		lst_name->value = NULL;
		lst_name->value = ft_strdup(path);
	}
	else
	{
		tmp = ft_strjoin(env_key, "=");
		fn_set_env(parsed_data, tmp);
	}
}

void		fn_cd(t_parsed_data *parsed_data)
{
	char	*path;
	char	*new_path;

	path = NULL;
	new_path = NULL;
	if ((new_path = fn_get_path(parsed_data)))
	{
		path = getcwd(path, PATH_MAX);
		if (!(chdir(new_path)))
		{
			fn_change_cd(parsed_data, path, "OLDPWD");
			free(path);
			path = NULL;
			path = getcwd(path, PATH_MAX);
			fn_change_cd(parsed_data, path, "PWD");
		}
		free(path);
		path = NULL;
		free(new_path);
		new_path = NULL;
	}
}
