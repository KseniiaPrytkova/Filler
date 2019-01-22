NAME = kprytkov.filler
# LIB_NAME = ./libftprintf/libftprintf.a

SRC_PROJECT = filler.c \
			# ./srcs/game_init.c \
			# ./srcs/del.c \
			# ./srcs/game_loop.c \
			# ./srcs/algorithm.c \
			# ./srcs/heat_map_fillers.c 

OBJECT_PROJECT = $(SRC_PROJECT:.c=.o)
FLAGS = -O3 -Wall -Wextra -Werror -I./includes -I./libftprintf/includes
# FLAGS_LIBFTPRINTF = -L./libftprintf -lftprintf

all: $(NAME)
	@echo '🦄 compiling a project "filler" for iMac'
	@gcc -o $(NAME) $(FLAGS) $(SRC_PROJECT) $(FLAGS_LIBFTPRINTF)
	@echo '🦄 ready!'

$(NAME): $(LIB_NAME) $(OBJECT_PROJECT)
	
$(LIB_NAME):
	@echo '🦄 recompiling an cleaning library libftprintf.a'
	@make -C ./libftprintf/ re
	@make -C ./libftprintf/ clean	

%.o: %.c
	@echo '🦄 updating changes in .c files'
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@echo '🦄 cleaning a project'
	@/bin/rm -f $(OBJECT_PROJECT)

fclean: clean
	@echo '🦄 removing a project'
	@/bin/rm -f $(NAME)
	@make -C ./libftprintf/ fclean

re:	fclean all
