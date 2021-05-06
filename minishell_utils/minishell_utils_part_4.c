/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_part_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:07:27 by mismene           #+#    #+#             */
/*   Updated: 2021/05/06 17:07:29 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char ***array)
{
	size_t	i;
	char	**p;

	p = *array;
	i = 0;
	while (p[i])
	{
		free_str(&p[i]);
		i++;
	}
	free(array);
}

void	print_array3(char ***array)
{
	int		i;
	int		ii;

	i = 0;
	while (array[i])
	{
		printf("%i\n", i);
		ii = 0;
		while (array[i][ii])
		{
			printf("%s\n", array[i][ii]);
			ii++;
		}
		printf("\n");
		i++;
	}
}

void	free_four(char **str1, char **str2, char **str3, char **str4)
{
	free_str(str1);
	free_str(str2);
	free_str(str3);
	free_str(str4);
}
