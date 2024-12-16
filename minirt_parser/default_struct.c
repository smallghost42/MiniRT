/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:33:39 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/16 10:16:44 by ferafano         ###   ########.fr       */
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

void init_shape(t_shape *shape)
{
	shape->sphere = NULL;
	shape->plane = NULL;
	shape->cylinder = NULL;
}

int alloc_data_default(t_data *data)
{
	data->ambient_lightning = malloc(sizeof(t_ambient_lightning));
	data->camera = malloc(sizeof(t_camera));
	data->light = malloc(sizeof(t_light));
	data->shape = malloc(sizeof(t_shape));
	if (!data->ambient_lightning || !data->camera || !data->light ||
		!data->shape)
		return (1);
	create_default_A_C_L(data);
	init_shape(data->shape);
	return (0);
}
