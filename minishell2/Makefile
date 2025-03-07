# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 13:47:34 by lloginov          #+#    #+#              #
#    Updated: 2025/03/07 17:24:49 by lloginov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
LFLAGS = -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS = -Wall -Wextra -Werror -lreadline -g #-fsanitize=address

SRC =	parsing/main.c		\
		parsing/utils.c		\
		parsing/utils2.c	\
		parsing/utils3.c	\
		parsing/spliting.c	\
		parsing/free_fonctions.c\
		parsing/tokenizer.c	\
		parsing/checker.c	\
		parsing/chain_list.c\
		parsing/signal.c	\
		parsing/dollar.c	\
		parsing/env.c		\
		parsing/last_chainlist.c\
		parsing/lst_cmd.c	\
		exec/find_env.c\
		exec/utils.c\
		exec/builtin1.c\
		exec/builtin2.c\
		exec/error_handling.c\
		exec/chain_lists.c\
		exec/utils2.c\
		exec/ft_join.c\
		exec/pathfinder.c\
		exec/exec_minishell.c\
		exec/builtin_cd.c\
		exec/utils3.c\

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