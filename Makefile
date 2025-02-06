# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 13:47:34 by lloginov          #+#    #+#              #
#    Updated: 2025/02/06 18:04:37 by lloginov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
CC = gcc
CFLAGS = -g2 -Wall -Wextra #-Werror    #-fsanitize=adress 

SRC =   src/minishell.c\
		src/find_env.c\
		src/utils.c\
		src/builtin1.c\
		src/error_handling.c\
		src/chain_lists.c\
		src/utils2.c\
		src/ft_join.c\

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