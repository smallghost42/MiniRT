/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 07:40:16 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/08 14:30:20 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
    
	// t_shape*				shape;
    // t_camera*				camera;
    // t_light*				light;
    // t_ambient_lightning*	ambient_light;

	// shape = data->shape;
	// camera = data->shape;
	// light = data->light;
	// ambient_light = data->ambient_lightning;

float	get_sphere_distance(t_sphere* sphere, t_ray ray, t_shape** visible_object)
{
	float		distance;
	float		min_distance;
	float		radius;
	t_sphere*	sphere_next;
	t_vec3		center;

	min_distance = INFINITY;
	if (!sphere)
		return (INFINITY);
	distance = get_sphere_pt_distance(ray, sphere->center, sphere->diameter / 2.0);
	if (distance >= 0 && distance < min_distance)
	{
		min_distance = distance;
		(*visible_object)->sphere = sphere;
	}
	sphere_next = sphere->next;
	while (sphere_next)
	{
		center = sphere_next->center;
		radius = sphere_next->diameter / 2.0;
		distance = get_sphere_pt_distance(ray, center, radius);
		if (distance >= 0 && distance < min_distance)
		{
			min_distance = distance;
			(*visible_object)->sphere = sphere_next;
		}
		sphere_next = sphere_next->next;
	}
	return (min_distance);
}

float	get_object_distance(t_data* data, t_ray ray, t_shape** visible_object)
{
	t_shape*	shape;
	float		distance;
	float		obj_distance[3];

	distance = INFINITY;
	shape = data->shape;
	// obj_distance[0] = get_plane_distance(shape->plane, ray, visible_object);
	// if (obj_distance[0] > 0 && obj_distance[0] < distance)
	// 	distance = obj_distance[0];
	obj_distance[1] = get_sphere_distance(shape->sphere, ray, visible_object);
	if (obj_distance[1] > 0 && obj_distance[1] < distance)
	{
		distance = obj_distance[1];
		(*visible_object)->plane = NULL;
	}
	// obj_distance[2] = get_cylinder_distance(shape->cylinder, ray, visible_object);
	// if (obj_distance[2] > 0 && obj_distance[2] < distance)
	// {
	// 	distance = obj_distance[2];
	// 	visible_object->plane = NULL;
	// 	visible_object->sphere = NULL;
	// }
	return (distance);
}

int	get_object_color(t_data* data, t_ray ray, t_shape** visible_object, float distance)
{
	int	color;

	color = 0;
	// if ((*visible_object)->plane)
	// 	color = get_plane_pt_color();
	if ((*visible_object)->sphere)
		// color = get_sphere_pt_color();
		color = (*visible_object)->sphere->color;
	// if ((*visible_object)->cylinder)
	// 	color = get_cylinder_pt_color();
	//check is this visible_object in shadow;
	return (color);
}

int	render_shape(t_data *data, t_ray ray, t_shape** visible_obj)
{
	int			color;
	float		distance;

	distance = get_object_distance(data, ray, visible_obj);
	if (distance == INFINITY || distance < 0)
		return (-1);
	color = get_object_color(data, ray, visible_obj, distance);
	return (color);
}

t_ray	ray_from_screen(t_data* data, int coord[2])
{
	t_ray		ray;
	float		img_coord[2];
	t_camera*	camera;

	camera = data->camera;
	img_coord[0] = get_x_projected(coord[0], camera->field_view);
	img_coord[1] = get_y_projected(coord[1], camera->field_view);
	ray = ray_create(camera->position, get_ray_direction(img_coord));
	return (ray);
}

t_shape*	init_visible_obj()
{
	t_shape*	visible_object;

	visible_object = malloc(sizeof(t_shape));
	if (!visible_object)
		return (NULL);
	visible_object->plane = NULL;
	visible_object->sphere = NULL;
	visible_object->cylinder = NULL;
	return (visible_object);
}

int render_scene(t_scene *scene)
{
	int			color;
	int			coord[2];
	t_shape*	visible_obj;
	t_ray		ray;

	coord[0] = 0;
	color = 0;
	visible_obj = init_visible_obj();
	while (coord[0] < WIN_WIDTH)
	{
		coord[1] = 0;
		while (coord[1] < WIN_HEIGHT)
		{
			ray = ray_from_screen(scene->data, coord);
			color = render_shape(scene->data, ray, &visible_obj);
			if (color > -1)
            	my_mlx_pixel_put(scene, coord[0], coord[1], color);
			coord[1]++;
		}
		coord[0]++;
	}
	free(visible_obj);
	return (0);
}
