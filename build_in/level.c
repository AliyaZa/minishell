/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:37:46 by nhill             #+#    #+#             */
/*   Updated: 2021/05/03 18:46:09 by nhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


void	level(t_parsed_data *parsed_data, t_command *command)
{
	t_env	*mini;
	int		level;

	if (fn_search(command->command, "minishell"))
	{
		mini = fn_get_el(parsed_data, "SHLVL");
		if (check_digit(mini->value) == 0)
			level = 0;
		else
			level = ft_atoi(mini->value);
		if ((level < 999))
		{
			if (!(mini->value = ft_itoa(level + 1)))
				fn_errors(command, errno);
		}
		else if (level == 999)
			mini->value = "";
		else if (level >= 1000)
		{
			mini->value = "1";
			fn_errors(command, TOO_HIGH);
		}
	}
}
