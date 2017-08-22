NAME = rt
CC = gcc
FLAGS = -Wall -Wextra
FLAGS2 = -Llibmath -lmath -L libft -lft -lmlx -lxml2 -lm -framework AppKit -framework OpenGL -framework OpenCL
INC = rt.h objects.h types.h
INCLUDE = $(INC:%.h=include/%.h)
SRC =	rt.c
OBJ = $(SRC:%.c=src/%.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -I include -I libft/include -I libmath/include -o $@ -c $<

libft/libft.a:
	make -C libft

~/.brew/lib/libxml2.a:
	brew install libxml2
	ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/lib/libxml2.a ~/.brew/lib/libxml2.a
	ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/lib/libxml2.dylib ~/.brew/lib/libxml2.dylib
	ln -sf ~/.brew/Cellar/libxml2/2.9.4.3/include/libxml2/libxml ~/.brew/include/libxml

$(NAME): ~/.brew/lib/libxml2.a $(OBJ) libft/libft.a
	export C_INCLUDE_PATH=/usr/local/include:~/.brew/include
	export LIBRARY_PATH=/usr/local/lib:~/.brew/lib
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

push: 
	git add -A
	git commit -m "Push makefile"
	git push
