NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c parser.c parser_utils.c valid_atof_atoi.c range_check.c ./range_check_elem.c ../lib/libft/ft_split.c ../lib/libft/get_next_line_bonus.c ./valid_rgb_normaliser.c ./add_back_plane.c ./add_back_sphere.c ./add_back_cylinder.c ./default_struct.c ../lib/libft/ft_strlen.c ../lib/libft/ft_substr.c ../lib/libft/ft_strchr.c ../lib/libft/ft_strjoin.c ../lib/libft/ft_strdup.c
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
