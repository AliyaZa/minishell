NAME = minishell

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = main.c parser.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) minishell.h
	gcc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all re clean fclean
