/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:48:54 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/11 17:36:38 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H

# define INCLUDE_H

# define WIN_WIDTH 1366

# define WIN_HEIGHT 768

# define PI 3.14162

# define COLOR 10523517

// # define EPSILON 0.000001

#define EPSILON 1e-4

# include "clib.h"

# include "vector.h"

# include "ray.h"

# include "utils.h"

# include "parser.h"

#include "test.h" //////////////////////to delete

typedef struct s_hit_pt
{
    t_shape *shape;
    int     type; //0, 1, 2
	t_vec3	pt;
    t_vec3  normal_vec;
    float   distance;
} t_hit_pt;

typedef struct s_scene
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			*offset;
	int			bpp;
	int			line_length;
	int			endian;
	t_data		*data;
	t_hit_pt	*hit_pt;
}	t_scene;

int render_scene(t_scene *scene);

//shape
t_vec3  ray_intersection_pt(t_ray ray, float distance);
t_vec3  pt_to_lightvec(t_light  *light, t_ray ray, t_hit_pt *hit_pt);
t_vec3  sp_pt_to_lightvec(t_vec3 light_pos, t_ray ray, float distance);
int		get_shade_lighting(t_data *data, t_ray ray, t_hit_pt *hit_pt);

//sphere
float   sphere_ray_hit_distance(t_ray ray, t_vec3 center, float radius);
t_vec3  sphere_normal_vec(t_ray ray, float distance, t_sphere* sphere);

//plane
float	plane_ray_hit_distance(t_ray ray, t_vec3 plane_pt, t_vec3 plane_normal);

//cylinder
t_vec3  cylinder_normal_vec(t_ray ray, t_cylinder* cylinder, float distance);
float   cylinder_ray_hit_distance(t_ray ray, t_cylinder* cylinder);

#endif