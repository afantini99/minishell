# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afantini <afantini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 14:03:16 by afantini          #+#    #+#              #
#    Updated: 2024/03/15 19:58:51 by afantini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc main.c parser.c executer.c libft/libft.h libft/ft_strlen.c libft/ft_strjoin.c -g -lreadline

NAME = minishell 

CC = gcc

CFLAGS = -Wall -Werror -Wextra -lreadline

LIB = libft/libft.a

SRC = main.c parser.c executer.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make all -C libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm

.SILENT:
