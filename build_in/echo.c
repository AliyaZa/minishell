/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <nhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:59:28 by nhill             #+#    #+#             */
/*   Updated: 2021/03/24 18:49:56 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fn_echo(t_parsed_data *parsed_data)
{
	write(1, parsed_data->argument, ft_strlen(parsed_data->argument));
	if (parsed_data->option != 'n')
	{
		write(1, "\n", 1);
		return ;
	}
}
