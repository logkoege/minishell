# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 13:47:34 by lloginov          #+#    #+#              #
#    Updated: 2025/02/23 19:47:54 by lloginov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
CC = gcc
CFLAGS = -g2 -Wall -Wextra  #-fsanitize=address #-Werror

SRC =   src/minishell.c\
		src/find_env.c\
		src/utils.c\
		src/builtin1.c\
		src/builtin2.c\
		src/error_handling.c\
		src/chain_lists.c\
		src/utils2.c\
		src/ft_join.c\
		src/pathfinder.c\
		src/exec_minishell.c\
		src/builtin_cd.c\
		src/utils3.c\

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