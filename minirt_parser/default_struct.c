/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:33:39 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/15 10:59:48 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "shape.h"

void create_default_A_C_L(t_data *data)
{
	data->ambient_lightning->color = 0x0fffff;
	data->ambient_lightning->lightning_ratio = 0.2;
	data->camera->position.x = 50.0;
	data->camera->position.y = 50.0;
	data->camera->position.z = 1.0;
	data->camera->field_view = 180;
	data->camera->orientation.x = 0.0;
	data->camera->orientation.y = 0.0;
	data->camera->orientation.z = 0.0;
	data->light->color = 0x0fffff;
	data->light->brightness_ratio = 0.5;
	data->light->position.x = 50.0;
	data->light->position.y = 50.0;
	data->light->position.z = 1.0;
}

void create_default_shape(t_shape *shape)
{
	shape->sphere->color = 0x0ffff;
	shape->sphere->center.x = 0;
	shape->sphere->center.y = 0;
	shape->sphere->center.z = 0;
	shape->sphere->diameter = 0;
	shape->sphere->next = NULL;
	shape->plane->color = 0x0ffff;
	shape->plane->center.x = 0;
	shape->plane->center.y = 0;
	shape->plane->center.z = 0;
	shape->plane->orientation.x = 0;
	shape->plane->orientation.y = 0;
	shape->plane->orientation.z = 0;
	shape->plane->next = NULL;
	shape->cylinder->color = 0x0fffff;
	shape->cylinder->orientation.x = 0;
	shape->cylinder->orientation.y = 0;
	shape->cylinder->orientation.z = 0;
	shape->cylinder->center.x = 0;
	shape->cylinder->center.y = 0;
	shape->cylinder->center.z = 0;
	shape->cylinder->diameter = 0;
	shape->cylinder->height = 0;
	shape->cylinder->next = NULL;
}

int alloc_default_shape(t_data *data)
{
	data->shape->sphere = malloc(sizeof(t_sphere));
	data->shape->plane = malloc(sizeof(t_plane));
	data->shape->cylinder = malloc(sizeof(t_cylinder));
	if (!data->shape->sphere || !data->shape->plane || !data->shape->cylinder)
		return (1);
	create_default_shape(data->shape);
	return (0);
}
int alloc_data_default(t_data *data)
{
	data->ambient_lightning = malloc(sizeof(t_ambient_lightning));
	data->camera = malloc(sizeof(t_camera));
	data->light = malloc(sizeof(t_light));
	data->shape = malloc(sizeof(t_shape));
	if (!data->ambient_lightning || !data->camera || !data->light || !data->shape)
		return (1);
	create_default_A_C_L(data);
	if (alloc_default_shape(data))
		return (1);
	return (0);
}
