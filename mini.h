#ifndef MINI_H
#define MINI_H

#include "file_parser/get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define WIN_WIDTH 1600
#define WIN_HEIGHT 800

typedef struct s_data
{
	void *img;
	void *mlx;
	void *mlx_win;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	struct s_var *var;
} t_data;

typedef struct s_count
{
	int a_l;
	int cam;
	int light;
	int sp;
	int pl;
	int cy;
} t_count;

int file_parser(char *filename);
char	**ft_split(char const *s, char c);

#endif
