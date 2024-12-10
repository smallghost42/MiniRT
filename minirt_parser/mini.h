#ifndef MINI_H
#define MINI_H

#include "./libft/get_next_line.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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
char **ft_split(char const *s, char c);
void free_split(char **str);
int valid_range_ambient(char **str2);
double ft_atof(const char *str);
int is_valid_float(char *str, int x);
int check_first_and_count_param(char *str, t_count *count);
int check_file_extention(char *filename);
int check_valid_rgb(char *color);
long ft_atoi(const char *nptr);
int ft_valid_int(const char *str);
int check_valid_coordinate(char *cord);
int valid_range_camera(char **str2);
int check_3dnormaliser(char *cord);
int valid_range_light(char **str2);
int valid_range_sphere(char **str2);

#endif
