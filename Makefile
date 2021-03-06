NAME = minishell

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = main.c \
	main_cycle.c save_history.c \
	navigate_history.c \
	structures_init.c router.c \
	minishell_utils/minishell_utils.c \
	minishell_utils/minishell_utils_part_2.c \
	minishell_utils/minishell_utils_part_3.c \
	minishell_utils/minishell_utils_part_4.c \
	validator/validator.c \
	validator/validator_part_2.c \
	validator/validator_part_3.c \
	validator/validator_part_4.c \
	build_in/echo.c \
	build_in/env.c \
	build_in/fn_export.c \
	build_in/fn_unset.c \
	build_in/pwd.c \
	build_in/fn_fork.c \
	build_in/fn_errors.c \
	build_in/command_utils.c \
	build_in/command_utils2.c \
	build_in/command_utils3.c \
	build_in/command_utils4.c \
	build_in/fn_cd.c \
	build_in/fn_pipe.c \
	build_in/level.c \
	parser/parser.c \
	parser/parse_env.c \
	parser/parser_utils.c \
	parser/parser_utils_part_2.c \
	parser/parser_utils_part_3.c \
	parser/parser_utils_part_4.c \
	parser/semicolon.c \
	termcap/termcap.c \
	termcap/termcap_utils.c \
	termcap/termcap_utils_part_2.c \

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
