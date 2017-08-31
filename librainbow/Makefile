NAME = librainbow.a
LIBSO = librainbow.so
CC = gcc
SRC =	new_window.c delete_window.c get_info.c new_image.c pixel_put.c draw_line.c\
		get_fps.c set_fps.c draw_triangle.c draw_polygone.c new_color.c
OBJ = $(SRC:%.c=src/%.o)
FLAGS = -Wall -Wextra
INC = librainbow.h private.h types.h
INCLUDE = $(INC:%.h=include/%.h)
LIBFT = ../libft
LIBIMAGES = ../libimages
LIBMATH = ../libmath

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
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT)/include -I $(LIBIMAGES)/include -I $(LIBMATH)/include -o $@ -c $<

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
