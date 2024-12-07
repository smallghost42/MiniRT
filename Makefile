NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c ./file_parser/parser.c ./file_parser/parser_utils.c ./file_parser/valid_atof.c ./file_parser/range_check_ambient.c ./libft/ft_split.c ./libft/get_next_line.c ./libft/get_next_line_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY:
	all bonus clean fclean re
