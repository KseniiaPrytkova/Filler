NAME = kprytkov.filler
LIB_NAME = ./libft/libft.a

SRC_PROJECT = src/filler.c \
              src/init_part.c \
			src/decision_part.c \
			# ./srcs/game_loop.c \
			# ./srcs/algorithm.c \
			# ./srcs/heat_map_fillers.c 

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
