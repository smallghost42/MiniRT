NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c ./file_parser/parser.c ./file_parser/get_next_line.c ./file_parser/get_next_line_utils.c ./file_parser/ft_split.c ./file_parser/parser_utils.c ./file_parser/range_check_ambient.c
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
