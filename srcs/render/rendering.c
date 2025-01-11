/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 07:40:16 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/11 17:38:56 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
    
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
	distance = sphere_ray_hit_distance(ray, sphere->center, sphere->diameter / 2.0);
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
		distance = sphere_ray_hit_distance(ray, center, radius);
		if (distance >= 0 && distance < min_distance)
		{
			min_distance = distance;
			(*visible_object)->sphere = sphere_next;
		}
		sphere_next = sphere_next->next;
	}
	return (min_distance);
}

float	get_plane_distance(t_plane* plane, t_ray ray, t_shape** visible_object)
{
	float		distance;
	float		min_distance;
	t_plane*	plane_next;
	t_vec3		orientation;
	t_vec3		center;

	min_distance = INFINITY;
	if (!plane)
		return (INFINITY);
	distance = plane_ray_hit_distance(ray, plane->center, plane->orientation);
	if (distance >= 0 && distance < min_distance)
	{
		min_distance = distance;
		(*visible_object)->plane = plane;
	}
	plane_next = plane->next;
	while (plane_next)
	{
		center = plane_next->center;
		orientation = plane_next->orientation;
		distance = plane_ray_hit_distance(ray, center, orientation);
		if (distance >= 0 && distance < min_distance)
		{
			min_distance = distance;
			(*visible_object)->plane = plane_next;
		}
		plane_next = plane_next->next;
	}
	return (min_distance);
}

float	get_cylinder_distance(t_cylinder* cylinder, t_ray ray, t_shape** visible_object)
{
	float		distance;
	float		min_distance;
	t_cylinder*	cylinder_next;
	float		diameter;
	float		height;
	t_vec3		orientation;
	t_vec3		center;

	min_distance = INFINITY;
	if (!cylinder)
		return (INFINITY);
	distance = cylinder_ray_hit_distance(ray, cylinder);
	if (distance >= 0 && distance < min_distance)
	{
		min_distance = distance;
		(*visible_object)->cylinder = cylinder;
	}
	cylinder_next = cylinder->next;
	while (cylinder_next)
	{
		center = cylinder_next->center;
		orientation = cylinder_next->orientation;
		diameter = cylinder_next->diameter;
		height = cylinder_next->height;
		distance = cylinder_ray_hit_distance(ray, cylinder_next);
		if (distance >= 0 && distance < min_distance)
		{
			min_distance = distance;
			(*visible_object)->cylinder = cylinder_next;
		}
		cylinder_next = cylinder_next->next;
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
	(*visible_object)->plane = NULL;
	(*visible_object)->sphere = NULL;
	(*visible_object)->cylinder = NULL;
	obj_distance[0] = get_plane_distance(shape->plane, ray, visible_object);
	if (obj_distance[0] > 0 && obj_distance[0] < distance)
		distance = obj_distance[0];		
	obj_distance[1] = get_sphere_distance(shape->sphere, ray, visible_object);
	if (obj_distance[1] > 0 && obj_distance[1] < distance)
	{
		distance = obj_distance[1];
		(*visible_object)->plane = NULL;
	}
	obj_distance[2] = get_cylinder_distance(shape->cylinder, ray, visible_object);
	if (obj_distance[2] > 0 && obj_distance[2] < distance)
	{
		distance = obj_distance[2];
		(*visible_object)->plane = NULL;
		(*visible_object)->sphere = NULL;
	}
	return (distance);
}

int	get_object_color(t_data* data, t_ray ray, t_hit_pt** hit_pt)
{
	int	color;
	int	is_shadowed;
	t_shape	*visible_obj;

	visible_obj = (*hit_pt)->shape;
	color = 0;
	if (visible_obj->plane)
		color = visible_obj->plane->color;
	else if (visible_obj->sphere)
		color = visible_obj->sphere->color;
	else if (visible_obj->cylinder)
		color = visible_obj->cylinder->color;
	// color = get_shade_lighting(data, ray, *hit_pt);
	//get shadow attenuation
	return (color);
}
// typedef struct s_hit_pt
// {
//     t_shape *shape;ok
//     int     type; //0, 1, 2
// 	t_vec3	pt;
//     t_vec3  normal_vec;
//     float   distance;
// } t_hit_pt;
void	update_hit_pt(t_hit_pt** hit_pt, float distance, t_ray ray)
{
	t_shape* shape;

	(*hit_pt)->distance = distance;
	shape = (*hit_pt)->shape;
	(*hit_pt)->normal_vec = ray_intersection_pt(ray, distance);
	if (shape->plane)
	{
		(*hit_pt)->type = 0;
		(*hit_pt)->normal_vec = shape->plane->orientation;
	}
	else if (shape->sphere)
	{
		(*hit_pt)->type = 1;
		(*hit_pt)->normal_vec = sphere_normal_vec(ray, distance, shape->sphere);
	}
	else if (shape->cylinder)
	{
		(*hit_pt)->type = 2;
		(*hit_pt)->normal_vec = cylinder_normal_vec(ray, shape->cylinder, distance);
	}
}

int	pixel_color(t_data *data, t_ray ray, t_hit_pt** hit_pt)
{
	int			color;
	float		distance;
	t_shape		**visible_obj;

	visible_obj = &((*hit_pt)->shape);
	distance = get_object_distance(data, ray, visible_obj);
	if (distance == INFINITY || distance < 0)
		return (-1);
	update_hit_pt(hit_pt, distance, ray);
	color = get_object_color(data, ray, hit_pt);
	return (color);
}

t_ray	visibility_ray(t_data* data, int coord[2])
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
	t_ray		ray;

	coord[0] = 0;
	color = 0;
	while (coord[0] < WIN_WIDTH)
	{
		coord[1] = 0;
		while (coord[1] < WIN_HEIGHT)
		{
			ray = visibility_ray(scene->data, coord);
			color = pixel_color(scene->data, ray, &(scene->hit_pt));
			if (color > -1)
            	my_mlx_pixel_put(scene, coord[0], coord[1], color);
			coord[1]++;
		}
		coord[0]++;
	}
	return (0);
}
