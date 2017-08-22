NAME = rt
CC = gcc
FLAGS = -Wall -Wextra
FLAGS2 = -Llibmath -lmath -L libft -lft -lmlx -lxml2 -lm -framework AppKit -framework OpenGL -framework OpenCL
INC = rt.h objects.h types.h
INCLUDE = $(INC:%.h=include/%.h)
SRC =	rt.c error.c flags.c
OBJ = $(SRC:%.c=src/%.o)

.PHONY: all clean fclean re norme push

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -I include -I libft/include -I libmath/include -o $@ -c $<

libft/libft.a:
	make -C libft

libmath/libmath.a:
	make -C libmath

~/.brew/lib/libxml2.a:
	brew install libxml2
	ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/lib/libxml2.a ~/.brew/lib/libxml2.a
	ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/lib/libxml2.dylib ~/.brew/lib/libxml2.dylib
	ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/include/libxml2/libxml ~/.brew/include/libxml

$(NAME): ~/.brew/lib/libxml2.a $(OBJ) libft/libft.a libmath/libmath.a
	export C_INCLUDE_PATH=/usr/local/include:~/.brew/include
	export LIBRARY_PATH=/usr/local/lib:~/.brew/lib
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2)

clean:
	make -C libft clean
	make -C libmath clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	make -C libmath fclean
	rm -f $(NAME)

re: fclean all

norme:
	@norminette $(OBJ:%.o=%.c) $(INCLUDE)

push: 
	git add -A
	git commit -m "Push makefile"
	git push
