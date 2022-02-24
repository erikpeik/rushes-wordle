#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acastano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 18:41:43 by acastano          #+#    #+#              #
#    Updated: 2022/02/24 18:55:44 by acastano         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = clang

CFLAGS = -Wall -Wextra -Werror

NAME = wordle

SRCS = wordle-assistant.c

HEADERS = ./libft/includes/

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft/
	$(CC) $(CFLAGS) -c $(SRCS) -I $(HEADERS)
	$(CC) -o $(NAME) $(OBJ) -I $(HEADERS) -L libft/ -lft

clean:
	@make clean -C libft/
	/bin/rm -f $(OBJ) *.c~ *.h~

fclean: clean
	@make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
