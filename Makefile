NAME = minishell
CC = gcc
LFLAGS = -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS = -Wall -Wextra -Werror -lreadline #-g -fsanitize=address
SRC = main.c		\
		parsing.c	\
		utils.c		\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re