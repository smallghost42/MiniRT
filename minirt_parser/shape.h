#ifndef SHAPE_H
#define SHAPE_H

#include "../includes/vector.h"

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

#endif
