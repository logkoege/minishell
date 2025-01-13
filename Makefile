NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRC = main.c		\
		parsing.c	\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re