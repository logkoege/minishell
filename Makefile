# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 13:47:34 by lloginov          #+#    #+#              #
#    Updated: 2025/04/03 18:22:30 by lloginov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
LFLAGS = -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS = -Wall -Wextra -Werror -lreadline -g3 #-fsanitize=address

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
		parsing/dollar2.c\
		parsing/token2.c\
		parsing/dollar3.c\
		parsing/dollar_utils.c\
		parsing/last_utils.c\
		exec/find_env.c\
		exec/utils.c\
		exec/builtin1.c\
		exec/builtin_unset.c\
		exec/utils2.c\
		exec/ft_join.c\
		exec/pathfinder.c\
		exec/exec_minishell.c\
		exec/builtin_cd.c\
		exec/utils3.c\
		exec/check_in-outfile.c\
		exec/builtin_export.c\
		exec/main_exec.c\
		exec/exec_fils.c\
		exec/builtin_exit.c\
		exec/export_utils.c\
		exec/export_utils2.c\
		exec/redirect_exec.c\
		exec/execute_pipes.c\
		exec/here_doc.c\

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
