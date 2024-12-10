#ifndef MINI_H
#define MINI_H

#include "./libft/get_next_line_bonus.h"
#include "./libft/libft.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef struct s_vec3
{
    float   x;
    float   y;
    float   z;
}   t_vec3;

typedef struct s_ambient_lightning
{
	double lightning_ratio;
	int color;
} t_ambient_lightning;

typedef struct s_camera
{
	t_vec3 position;
	t_vec3 orientation;
	int field_view;
} t_camera;

typedef struct s_light
{
	t_vec3 position;
	double brightness_ratio;
	int color;
} t_light;

typedef struct s_sphere
{
	t_vec3 center;
	double diameter;
	int color;
	struct s_sphere *next;
} t_sphere;

typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 orientation;
	double diameter;
	double height;
	int color;
	struct s_cylinder *next;
} t_cylinder;

typedef struct s_plane
{
	t_vec3 center;
	t_vec3 orientation;
	int color;
	struct s_plane *next;
} t_plane;

typedef struct s_shape
{
	t_sphere *sphere;
	t_cylinder *cylinder;
	t_plane *plane;
} t_shape;

typedef struct s_data
{
	t_ambient_lightning *ambient_lightning;
	t_camera *camera;
	t_light *light;
	t_shape *shape;
} t_data;

typedef struct s_count
{
	int a_l;
	int cam;
	int light;
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
int ft_atoi(const char *nptr);
int ft_valid_int(const char *str);
int check_valid_coordinate(char *cord);
int valid_range_camera(char **str2);
int check_3dnormaliser(char *cord);
int valid_range_light(char **str2);
int valid_range_sphere(char **str2);
int valid_range_plane(char **str2);
int valid_range_cylinder(char **str2);

#endif
