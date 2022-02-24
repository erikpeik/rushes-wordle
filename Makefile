#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acastano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 18:41:43 by acastano          #+#    #+#              #
#    Updated: 2022/02/24 23:18:22 by acastano         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = clang

CFLAGS = -Wall -Wextra -Werror

NAME = wordle-assistant
NAME2 = wordle-player

SRCS = wordle-assistant.c
SRCS2 = wordle-player.c

HEADERS = ./libft/includes/

OBJ = $(SRCS:.c=.o)
OBJ2 = $(SRCS2:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft/
	$(CC) $(CFLAGS) -c $(SRCS) -I $(HEADERS)
	$(CC) -o $(NAME) $(OBJ) -I $(HEADERS) -L libft/ -lft
	$(CC) $(CFLAGS) -c $(SRCS2) -I $(HEADERS)
	$(CC) -o $(NAME2) $(OBJ2) -I $(HEADERS) -L libft/ -lft

clean:
	@make clean -C libft/
	/bin/rm -f $(OBJ) *.c~ *.h~
	/bin/rm -f $(OBJ2) *.c~ *.h~

fclean: clean
	@make fclean -C libft/
	/bin/rm -f $(NAME)
	/bin/rm -f $(NAME2)

re: fclean all

.PHONY = all clean fclean re
