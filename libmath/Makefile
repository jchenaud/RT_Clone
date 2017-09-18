NAME = libmath.a
LIBSO = libmath.so
CC = gcc
SRC =	vector/add.c vector/cross.c vector/debug.c vector/mult.c vector/new.c\
		vector/normalize.c vector/scalar.c vector/sub.c vector/rotate.c\
		matrix/clean.c matrix/debug.c matrix/lookat.c matrix/mat_x_mat.c\
		matrix/mat_x_vec.c matrix/new.c matrix/perspective.c matrix/set_id.c
OBJ = $(SRC:%.c=src/%.o)
FLAGS = -Wall -Wextra -Werror
INC = libmath.h
INCLUDE = $(INC:%.h=include/%.h)
LIBFT = ../libft

.PHONY: clean fclean all re norme newline

all: $(NAME)

$(LIBSO): $(OBJ)
	@echo "\033[38;5;214mmaking $@\033[0m"
	@$(CC) $(FLAGS) -shared -o $(LIBSO) $(OBJ)
	@echo "\033[38;5;214m$@ done\033[0m"

$(NAME): $(OBJ)
	@echo "\033[38;5;214mmaking $@\033[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[38;5;214m$@ done\033[0m"

%.o: %.c $(INCLUDE)
	@echo "\033[38;5;226mmaking $@\033[0m"
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT)/include -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@echo "\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBSO)
	@echo "\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJ:%.o=%.c) $(INCLUDE)

re: fclean all