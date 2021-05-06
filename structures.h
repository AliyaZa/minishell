/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:20:19 by mismene           #+#    #+#             */
/*   Updated: 2021/05/06 17:20:21 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_parsed_data
{
	char		**history;
	t_env		*env_data;
}				t_parsed_data;

typedef	struct	s_flags
{
	int			is_bin;
	int			rev_redirect;
	int			error;
	int			pipe;
}				t_flags;

typedef struct	s_command
{
	char		*raw_string;
	char		*command;
	char		option;
	char		*argument;
	char		*rest_string;
	char		quotes_type;
	char		*queue;
	char		***pipes;
	size_t		pipes_quantity;
	int			fd[2];
	t_flags		*flags;
}				t_command;

#endif
