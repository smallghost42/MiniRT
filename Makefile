SRCS = $(wildcard srcs/*.c)

OBJS = ${SRCS:.c=.o}

CC = cc

RM = rm -f

CFLAGS = -Werror -Wextra -Werror -Iincludes

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

MLX_PATH = ./mlx

MLX_NAME = libmlx.a

MLX = ${MLX_PATH}/${MLX_NAME}

LIBFT_PATH = ./libft

LIBFT_NAME = libft.a

LIBFT = ${LIBFT_PATH}/${LIBFT_NAME}

NAME = miniRT

%.o: %.c
	@$(CC) ${CFLAGS} -I/usr/include -Imlx -Ilibft -O3 -c $< -o $@

all: ${NAME}

${LIBFT}:
		make -sC ${LIBFT_PATH}
${MLX} :
		make -sC ${MLX_PATH}

$(NAME):  ${OBJS} ${LIBFT}  ${MLX} 
	@$(CC) ${CFLAGS} ${OBJS}  ${MLX_FLAGS} -Llibft -lft -Ilibft -o $(NAME)

clean:
		make -sC ${MLX_PATH} clean
		make -sC ${LIBFT_PATH} clean
		rm -rf ${OBJS} 	

fclean:  clean
		make -sC ${LIBFT_PATH} fclean
		rm -rf ${NAME}

re:  fclean all