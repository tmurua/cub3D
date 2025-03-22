NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

MINILIBX = ./minilibx-linux
LIBFT	= ./libft/libft.a

# Source Files
SRC		=	main.c \
			input_handler.c parse_map.c get_next_line.c \
			error_utils.c process_line.c

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
