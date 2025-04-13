NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

MINILIBX = ./minilibx-linux
LIBFT	= ./libft/libft.a

# Source Files
SRC		=	./src/main.c \
			./src/input/input_handler.c \
			./src/error/error_utils.c \
			./src/parser/parse_cub_file.c \
			./src/parser/process_line.c \
			./src/parser/get_next_line.c \
			./src/parser/parse_texture.c \
			./src/parser/parse_color.c \
			./src/parser/validate_map_requirements.c \
			./src/parser/flood_fill_algorithm.c \
			./src/parser/map_padding.c \
			./src/game/game_cleanup.c \
			./src/raycaster/hooks.c \
			./src/raycaster/raycaster.c \
			./src/raycaster/movement.c \
			./src/raycaster/textures.c \
			./src/raycaster/rendering.c \
			./src/raycaster/utils.c \
			./src/raycaster/radiocar.c \
			./src/init/init_game.c \
			./src/init/init_player.c \
			./src/init/init_map.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) minilibx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L$(MINILIBX) -lmlx -lXext -lX11 -lm
	echo "$(NAME) generated"

$(LIBFT):
	make -C ./libft --no-print-directory
	make bonus -C ./libft --no-print-directory
	echo "libft compiled"

minilibx:
	make -C $(MINILIBX) --no-print-directory > /dev/null 2>&1
	echo "minilibX compiled"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft --no-print-directory
	- make clean -C $(MINILIBX) --no-print-directory > /dev/null 2>&1
	rm -f $(OBJ)
	echo "object files deleted"
	rm -f $(MINILIBX)/Makefile.gen $(MINILIBX)/test/Makefile.gen > /dev/null 2>&1

fclean: clean
	make fclean -C ./libft --no-print-directory
	- make clean -C $(MINILIBX) --no-print-directory > /dev/null 2>&1
	rm -f $(NAME)
	echo "$(NAME) deleted"
	rm -f $(MINILIBX)/Makefile.gen $(MINILIBX)/test/Makefile.gen > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re minilibx

.SILENT:
