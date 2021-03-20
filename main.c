/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:10:30 by nhill             #+#    #+#             */
/*   Updated: 2021/03/20 13:52:07 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser allocate memory, free it after usage
int		main()
{
	t_parsed_data	*parsed_data;

	parsed_data = parser();
	printf("%s\n", parsed_data->rest_string);
	return (0);
}
