NAME = minishell


CFLAGS = -Wall -Wextra -Werror

SRC = main.c

OBJ = $(SRC:.c=.o)

objects: $(SRC)
	gcc $(CFLAGS) -c $(SRC)

all: $(objects) $(NAME)

$(NAME): $(SRC) minishell.h
	gcc $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all re clean fclean objects
