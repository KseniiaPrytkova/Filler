# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#              #
#    Updated: 2019/10/31 20:44:44 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = kprytkov.filler
LIB_NAME = ./libft/libft.a
SRC_PROJECT =	src/filler.c \
				src/init_part.c \
				src/create_hot_map.c \
				src/make_decision_part.c \
				src/piece_calc.c \
				src/alg.c \
				src/get.c \
				src/count_delta.c \
				src/hot_map_catch_next.c \
				src/create_hot_map_aux.c \
				src/free.c \
#OBJECT_PROJECT = $(SRC_PROJECT:.c=.o)
FLAGS = -O3 -Wall -Wextra -Werror -Iinclude/ -Ilibft/ -Llibft/ -lft

all: $(NAME)
	@echo '🦄 compiling a project "filler" for you Mac'
	@gcc -o $(NAME) $(SRC_PROJECT) $(FLAGS)
	@echo '🦄 ready!'

$(NAME): $(LIB_NAME) #$(OBJECT_PROJECT)
	
$(LIB_NAME):
	@make -C ./libft/ re
	@make -C ./libft/ clean	

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJECT_PROJECT)

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft/ fclean

re:	fclean all
