NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE_DIRS = -I/usr/include -Iminilibx-linux
SRC = main.c ./parser/check_file.c
OBJ = $(SRC:.c=.o)
LDFLAGS = -Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_PATH = ./minilibx-linux/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -O3 -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(MLX_PATH)
	$(CC) $(INCLUDE_DIRS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY:
	all bonus clean fclean re
