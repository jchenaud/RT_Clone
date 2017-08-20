NAME = rt
CC = gcc
FLAGS = -Wall -Wextra
FLAGS2 = -L libft -lft -lmlx -framework AppKit -framework OpenGL -framework OpenCL
INC = rt.h objects.h
INCLUDE = $(INC:%.h=include/%.h)
SRC = rt.c
OBJ = $(SRC:%.c=src/%.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -I include -o $@ -c $<

libft/libft.a:
	make -C libft

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
