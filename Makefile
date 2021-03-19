NAME = minishell

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = main.c parser.c minishell_utils.c validator.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) minishell.h
	gcc $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) -g

clean:
	rm -rf $(OBJ)
	make fclean -C libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
