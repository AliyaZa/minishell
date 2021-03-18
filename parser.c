/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:25:06 by mismene           #+#    #+#             */
/*   Updated: 2021/03/18 08:42:28 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsed_data	*parser()
{
	t_parsed_data	*parsed_data;

	parsed_data = malloc(sizeof(t_parsed_data));
	printf("hello world!");
	return (parsed_data);
}
