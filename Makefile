# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/17 18:10:52 by adu-pelo          #+#    #+#              #
#    Updated: 2016/11/09 14:18:27 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_select

C_DIR	= sources
C_DIRS	= $(shell find $(C_DIR) -type d -follow -print)
C_FILES	= $(shell find $(C_DIRS) -type f -follow -print | grep -w "[.c]$$")

O_DIR	= .tmp/obj
O_DIRS	= $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES	= $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS	= -Wall -Werror -Wextra
INCS	= -Iincludes -Ilibft
LIB		= -L./libft -lft -ltermcap

all: $(NAME)

$(NAME): $(O_FILES)
	@echo "Creating $(NAME)"
	@make -C ./libft
	@gcc $(FLAGS) $^ $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@echo "Creating object : $@"
	@mkdir -p $(O_DIRS) $(O_DIR)
	@gcc $(FLAGS) $(INCS) -o $@ -c $<

clean:
	@echo "Deleting objects"
	@rm -rf $(O_FILES)
	@make clean -C libft

fclean: clean
	@echo "Deleting $(NAME)"
	@make fclean -C libft
	@rm $(NAME) || true
	@rm -rf .tmp/

re: fclean all

.PHONY : all clean fclean re
