NAME = minishell

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = main.c parser.c minishell_utils.c validator.c parse_env.c echo.c env.c \
	main_cycle.c minishell_utils_part_2.c save_history.c router.c pwd.c init.c \
	spec_symbol.c termcap.c
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
