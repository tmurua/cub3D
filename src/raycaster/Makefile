NAME = raycaster
HEADER = raycaster.h
FLAGS = -Wall -Werror -Wextra -g
SRC = hooks.c raycaster.c movement.c textures.c rendering.c utils.c
OBJ = $(SRC:.c=.o)
CC = cc
LIBFT_DIR = ../../libft
LIBFT_MAKE = $(LIBFT_DIR)/Makefile
LIBFT = $(LIBFT_DIR)/libft.a

LFLAGS = -Imlx_linux -lXext -lX11 -lm -lz
MLX_DIR = ../../minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx
MLX_A = ../../minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_A)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_LIB) -L/usr/lib/ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Iminilibx-linux -Iinclude -c $< -o $@

$(MLX_A):
	cd ../../minilibx-linux; bash ./configure

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	- make clean -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	rm -f $(OBJ)
	rm -f $(MLX_DIR)/Makefile.gen $(MLX_DIR)/test/Makefile.gen > /dev/null 2>&1

fclean: clean
	make -C $(LIBFT_DIR) fclean
	- make clean -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	rm -f $(NAME)
	rm -f $(MLX_DIR)/Makefile.gen $(MLX_DIRX)/test/Makefile.gen > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re
