/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:27:05 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/07 09:14:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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

typedef struct s_data
{
	t_ambient_lightning *ambient_lightning;
	t_camera *camera;
	t_light *light;
	t_shape *shape;
} t_data;

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
*/

#include "minirt.h"

void    print_plane(t_plane *plane)
{
    printf("-----------------------------\n");
    printf("center:\n");
    vec3_print(plane->center);
    printf("orientation:\n");
    vec3_print(plane->orientation);
    printf("color = %d\n", plane->color);
}

void    print_cylinder(t_cylinder *cylinder)
{
    printf("-----------------------------\n");
    printf("center:\n");
    vec3_print(cylinder->center);
    printf("orientation:\n");
    vec3_print(cylinder->orientation);
    printf("diameter = %f and height = %f and color = %d\n", cylinder->diameter, cylinder->height, cylinder->color);
}

void    print_sphere(t_sphere *sphere)
{
    printf("-----------------------------\n");
    printf("center:\n");
    vec3_print(sphere->center);
    printf("diameter = %f and color = %d\n", sphere->diameter, sphere->color);
}


void    print_shape(t_shape *shape)
{
    t_sphere    *sphere = shape->sphere;
    if (sphere)
    {
        printf("\n************************************** sphere **************************************\n");
        print_sphere(sphere);
        t_sphere*   tmp = sphere->next;
        while (tmp)
        {
            print_sphere(tmp);
            tmp = tmp->next;
        }
    }
    t_cylinder    *cylinder = shape->cylinder;
    if (cylinder)
    {
        printf("\n************************************** cylinder **************************************\n");
        print_cylinder(cylinder);
        t_cylinder*   tmp = cylinder->next;
        while (tmp)
        {
            print_cylinder(tmp);
            tmp = tmp->next;
        }
    }
    t_plane    *plane = shape->plane;
    if (plane)
    {
        printf("\n************************************** plane **************************************\n");
        print_plane(plane);
        t_plane*   tmp = plane->next;
        while (tmp)
        {
            print_plane(tmp);
            tmp = tmp->next;
        }
    }
}

void    print_data(t_data *data)
{
    //ambient light
    t_ambient_lightning*    ambient_light = data->ambient_lightning;
    printf("\n************************************** ambient light **************************************\n");
    printf("ambient_ratio = %f and ambient_color = %d\n", ambient_light->lightning_ratio, ambient_light->color);
    //camera
    t_camera*   camera = data->camera;
    printf("\n************************************** camera **************************************\n");
    printf("position:\n");
    vec3_print(camera->position);
    printf("orientation:\n");
    vec3_print(camera->orientation);
    printf("fov = %d\n", camera->field_view);
    //light
    printf("\n************************************** light **************************************\n");
    t_light *light = data->light;
    printf("position:\n");
    vec3_print(light->position);
    printf("brightness_ratio = %f and color = %d\n", light->brightness_ratio, light->color);
    //shape
    print_shape(data->shape);
}
