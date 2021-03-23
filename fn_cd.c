/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:35:24 by nhill             #+#    #+#             */
/*   Updated: 2021/03/23 15:46:01 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2/minishell.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/dir.h>
#include <sys/syslimits.h>

t_env		*fn_get_el(t_env *our_env, char *key)
{
	while (our_env && !fn_search(our_env->key, key))
		our_env = our_env->next;
	if (our_env)
		return (our_env);
	return (NULL);
}

char		*fn_strjoin3(char *str1, char *str2, char *str3)
{
	char	*str;
	size_t	size;
	if (ft_strncmp(str1, "/", 1))
		size = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	else
		size = ft_strlen(str2) + ft_strlen(str3);
	if (!(str = malloc(size)))
		return(NULL);
	else
		ft_bzero(str,size);
	if (ft_strncmp(str1, "/", 1))
		str = ft_strlcpy(str, str1);
	str = ft_strlcat(str, str2);
	str = ft_strlcat(str, str3);
	return(str);
}

static char	*fn_new_path(char *parsed_data, t_env *home)
{
	char	*path;
	char	*new_path;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (new_path == parsed_data)
		fn_strjoin3(path, "/", parsed_data);
	else
		ft_strdup(home->value);
	free(path);
	path = NULL;
	return (new_path);
}

static char	*fn_get_path(char *parsed_data, t_env *our_env)
{
	char	*new_path;
	t_env	*home;
	t_env	*tmp;

	new_path = NULL;
	home = NULL;
	tmp = NULL;
	if ((!(home = fn_get_el(our_env, "HOME")) && !parsed_data))
		return (NULL);
	else if (parsed_data && parsed_data[0] == '/')
		new_path = ft_strdup(parsed_data);
	else if (fn_search(parsed_data, "~"))
	{
		if (!fn_get_el(our_env, "OLDPWD"))
			return (NULL);
		else
		{
			tmp = fn_get_el(our_env, "OLDPWD");
			new_path = ft_strdup(tmp->value);
		}
	}
	else
		new_path = fn_new_path(parsed_data, home);
	return (new_path);
}

char	*fn_strcreate(char *s, int start, char c)
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

t_env	*fn_create_el(char *env)
{
	t_env	*new_el;
	int		len;

	new_el = malloc(sizeof(t_env));
	len = ft_strchr(env, '=') - env;
	new_el->key = fn_strcreate(env, 0, len);
	new_el->value = fn_strcreate(env, len + 1, ft_strlen(env) - len);
	new_el->next = NULL;
	return (new_el);
}

void	fn_set_env(t_env **our_env, char *parsed_data)
{
	t_env	*env;
	char	*value;
	t_env	*env_copy;

	env = NULL;
	env_copy = *our_env;
	value = NULL;
	if (ft_strchr(parsed_data, '='))
	{
		value = fn_strcreate(parsed_data, 0, '=');
		while (env_copy && !fn_search(env_copy->value, value))
		{
			env_copy = env_copy->next;
		}
		free(value);
		if (env_copy)
		{
			free(env_copy->value);
			env_copy->value = ft_strdup((parsed_data + ft_strlen(env_copy->key) + 1));
		}
		else
		{
			env = fn_create_el(parsed_data);
			ft_lstadd_back2(our_env, env);
		}
	}
	else
		return ;
}

void	fn_change_cd(t_env **our_env, char *path, char *env_key)
{
	t_env	*lst_name;
	char	*tmp;

	lst_name = NULL;
	tmp = NULL;
	if ((lst_name = fn_get_el(*our_env, env_key)))
	{
		free(lst_name->value);
		lst_name->value = ft_strdup(path);
	}
	else
	{
		tmp = ft_strjoin(env_key, "=");
	}
}

void		fn_cd(t_env **our_env, char *parsed_data)
{
	char	*path;
	char	*new_path;

	path = NULL;
	new_path = NULL;
	if ((new_path = fn_get_path(parsed_data, *our_env)))
	{
		if (!(chdir(new_path)))
		{
			fn_change_cd(our_env, path, "OLDPWD");
			free(path);
			path = getcwd(path, PATH_MAX);
			fn_change_cd(our_env, path, "PWD");
		}
		free(path);
	}
}
