SRCS = $(wildcard srcs/*.c) $(wildcard srcs/*/*.c)

OBJS = ${SRCS:.c=.o}

CC = cc

RM = rm -f

CFLAGS = -Werror -Wextra -Werror -Iincludes -I${MLX_PATH}

MLX_FLAGS = -L${MLX_PATH} -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

MLX_PATH = ./lib/mlx

MLX_NAME = libmlx.a

MLX = ${MLX_PATH}/${MLX_NAME}

LIBFT_PATH = ./lib/libft

LIBFT_NAME = libft.a

LIBFT = ${LIBFT_PATH}/${LIBFT_NAME}

NAME = miniRT

%.o: %.c
	@$(CC) ${CFLAGS} -I/usr/include -I${MLX_PATH} -Ilibft -O3 -c $< -o $@

all: ${NAME}

${LIBFT}:
		make -sC ${LIBFT_PATH}
${MLX} :
		make -sC ${MLX_PATH}

$(NAME):  ${OBJS} ${LIBFT}  ${MLX} 
	@$(CC) ${CFLAGS} ${OBJS}  ${MLX_FLAGS} -L${LIBFT_PATH} -lft -Ilibft -o $(NAME)
	@echo "Build success!!!!!!!!"

clean:
		make -sC ${MLX_PATH} clean
		make -sC ${LIBFT_PATH} clean
		rm -rf ${OBJS} 	

fclean:  clean
		make -sC ${LIBFT_PATH} fclean
		rm -rf ${NAME}

re:  fclean all
