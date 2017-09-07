NAME = rt
CC = gcc
FLAGS = -Wall -Wextra
FLAGS2 = -L libmath -lmath -L libft -lft -L libimages -limages -L librainbow -lrainbow -lxml2 -lm -lz -lSDL2 -lSDL2_image -framework OpenCL
INC = rt.h objects.h types.h cl_struct.h
INCLUDE = $(INC:%.h=include/%.h)
SRC =	rt.c error.c flags.c hooks.c loop.c window.c antialiasing.c cam_rays.c intersection.c calc_rays.c shortcuts.c draw_image.c parsing/parsing.c
OBJ = $(SRC:%.c=src/%.o)
INCLUDES = -I include -I libft/include -I libmath/include -I libimages/include -I librainbow/include

.PHONY: all clean fclean re norme push

all: $(NAME)

%.o: %.c $(INCLUDE)
	@echo "\033[38;5;204mmaking $@\033[0m"
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

libft/libft.a:
	@make -C libft

libmath/libmath.a:
	@make -C libmath

libimages/libimages.a:
	@make -C libimages

librainbow/librainbow.a:
	@make -C librainbow

~/.brew/lib/libSDL2.a:
	@brew install sdl2

~/.brew/lib/libxml2.a:
	@brew install libxml2
	@ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/lib/libxml2.a ~/.brew/lib/libxml2.a
	@ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/lib/libxml2.dylib ~/.brew/lib/libxml2.dylib
	@ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/include/libxml2/libxml ~/.brew/include/libxml

$(NAME): ~/.brew/Cellar/libxml2/2.9.4_3/lib/libxml2.a ~/.brew/lib/libSDL2.a libft/libft.a libmath/libmath.a libimages/libimages.a librainbow/librainbow.a $(OBJ)
	@export C_INCLUDE_PATH=/usr/local/include:~/.brew/include
	@export LIBRARY_PATH=/usr/local/lib:~/.brew/lib
	@echo "\033[38;5;196mmaking $@\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2)

clean:
	@make -C libft clean
	@make -C libmath clean
	@make -C libimages clean
	@make -C librainbow clean
	@rm -f $(OBJ)
	@echo "\033[38;5;124mobject files removed\033[0m"

fclean: clean
	@make -C libft fclean
	@make -C libmath fclean
	@make -C libimages fclean
	@make -C librainbow fclean
	@rm -f $(NAME)
	@echo "\033[38;5;124m$(NAME) removed\033[0m"

re: fclean all

norme:
	@norminette $(OBJ:%.o=%.c) $(INCLUDE)
	@make -C libft norme
	@make -C libmath norme
	@make -C libimages norme
	@make -C librainbow norme

push:
	git add -A
	git commit -m "Push makefile"
	git push
