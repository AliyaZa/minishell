/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:21:10 by mismene           #+#    #+#             */
/*   Updated: 2021/03/18 12:24:18 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnew(unsigned int size)
{
	char	*string;

	string = malloc((sizeof(char) * size) + 1);
	if (string == NULL)
		return (NULL);
	string[size] = 0;
	return (string);
}
