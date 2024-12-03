#ifndef MINI_H
#define MINI_H

#include "minilibx-linux/mlx.h"
#include "utils1.c/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 800

typedef struct s_data
{
	void			*img;
	void			*mlx;
	void			*mlx_win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	struct s_var	*var;
}					t_data;

int file_parser(char *filename);

#endif
