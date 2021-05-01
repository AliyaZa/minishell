# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhill <nhill@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/01 19:51:09 by nhill             #+#    #+#              #
#    Updated: 2021/05/01 19:51:38 by nhill            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = main.c  minishell_utils.c \
	main_cycle.c minishell_utils_part_2.c save_history.c \
	termcap.c navigate_history.c termcap_utils.c validator.c \
	structures_init.c router.c minishell_utils_part_3.c\
	semicolon.c \
	validator_part_2.c \
	build_in/echo.c \
	build_in/env.c \
	build_in/fn_export.c \
	build_in/fn_unset.c \
	build_in/pwd.c \
	build_in/fn_fork.c \
	build_in/fn_errors.c \
	build_in/command_utils.c \
	build_in/command_utils2.c \
	build_in/fn_cd.c \
	parser/parser.c \
	parser/parse_env.c \
	parser/parser_utils.c \
	parser/parser_utils_part_2.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) minishell.h
	gcc -g $(CFLAGS) $(SRC) libft/libft.a -ltermcap -o $(NAME)

clean:
	rm -rf $(OBJ)
	make fclean -C libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
