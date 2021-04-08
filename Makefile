NAME = minishell

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = main.c parser.c minishell_utils.c validator.c parse_env.c \
	main_cycle.c minishell_utils_part_2.c save_history.c router.c  \
	spec_symbol.c termcap.c navigate_history.c termcap_utils.c semicolon.c \
	libft_modified.c structures_init.c
#build_in/echo build_in/env build_in/fn_cd build_in/fn_export build_in/fn_unset build_in/pwd \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft
	make bonus -C libft

$(NAME): $(OBJ) minishell.h
	gcc -g $(CFLAGS) $(SRC) libft/libft.a -ltermcap -o $(NAME)

clean:
	rm -rf $(OBJ)
	make fclean -C libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
