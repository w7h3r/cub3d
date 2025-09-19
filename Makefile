NAME=cub3D
CC=cc
CFLAGS=-Wall -Wextra -Werror -g
MLX_FLAGS=-lXext -lX11 -lm -lbsd
SRC=main.c \
	# src/parsing.c \
	# src/rendering.c \
	# src/movement.c \
	# src/utils.c \
	# src/raycasting.c \
	# src/drawing.c \
	# src/texture.c \
	# src/free.c
OBJ=$(SRC:.c=.o)
LIBFT=lib/libft/libft.a
MINILIBX=lib/minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C lib/libft/

$(MINILIBX):
	@make -C lib/minilibx-linux/

clean:
	@make -C lib/libft/ clean
	@make -C lib/minilibx-linux/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C lib/libft/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
