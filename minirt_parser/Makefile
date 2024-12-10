NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c parser.c parser_utils.c valid_atof_atoi.c range_check.c ./range_check_elem.c ./libft/ft_split.c ./libft/get_next_line.c ./libft/get_next_line_utils.c ./valid_rgb_normaliser.c
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


####all src without libft
#
#main.c parser.c parser_utils.c valid_atof_atoi.c range_check.c ./range_check_elem.c ./valid_rgb_normaliser.c
#
