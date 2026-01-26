NAME=cub3D
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -I./inc
MLX_DIR=lib/minilibx-linux
MLX_FLAGS=-L$(MLX_DIR) -lmlx -lXext -lX11 -lm
SRC=	src/main.c						\
		src/draw_utils.c				\
		src/init.c						\
		src/renderer.c					\
		src/hooks.c						\
		src/player_movement.c			\
		src/prep_render.c				\
		src/time.c						\
		src/parser/handle_map.c			\
		src/mem_alloc.c					\
		src/rays.c						\
		src/events.c					\
		src/parser/read_file.c			\
		src/parser/map_algorithm.c 		\
		src/parser/map_utils.c 			\
		src/parser/texture_parsing.c 	\
		src/parser/parse_utils/error_utils.c	\
		src/parser/parse_utils/ft_split.c		\
		src/parser/parse_utils/utils.c			\
		src/parser/parse_utils/list_utils.c 	\
		lib/get_next_line/get_next_line.c \
		lib/get_next_line/get_next_line_utils.c \

OBJ=$(SRC:.c=.o)
LIBFT=lib/libft/libft.a
MINILIBX=$(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -Ilib/libft -Iinclude -c $< -o $@

$(LIBFT):
	@make -C lib/libft/

$(MINILIBX):
	@make -C $(MLX_DIR)/

clean:
	@make -C lib/libft/ clean
	@make -C $(MLX_DIR)/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C lib/libft/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
