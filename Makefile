# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/17 18:10:52 by adu-pelo          #+#    #+#              #
#    Updated: 2016/05/17 18:21:02 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

C_DIR = src
C_FILES = $(shell find $(C_DIR) -type f -follow -print | grep "\.c")

OBJ = $(C_FILES:.c=.o)
	FLAGS = -Wall -Werror -Wextra
	LIB = -L./libft -lft

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAGS) -lncurses $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean :
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re
