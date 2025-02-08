NAME = minishell
CC = gcc
LFLAGS = -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS = -Wall -Wextra -Werror -lreadline #-g -fsanitize=address
SRC = main.c		\
		utils.c		\
		utils2.c	\
		utils3.c	\
		spliting.c	\
		free_fonctions.c\
		tokenizer.c	\
		checker.c	\
		chain_list.c\
		signal.c	\
		dollar.c	\
		env.c		\

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
