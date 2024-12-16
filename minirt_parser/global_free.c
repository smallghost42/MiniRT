/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:51:19 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/16 10:46:34 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "shape.h"

void free_data_plane(t_data *data)
{
	t_plane *tmp;
	t_plane *tmp2;

	tmp = data->shape->plane->next;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	if (data->shape->plane)
		free(data->shape->plane);
}

void free_data_sphere(t_data *data)
{
	t_sphere *tmp;
	t_sphere *tmp2;

	tmp = data->shape->sphere->next;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	if (data->shape->sphere)
		free(data->shape->sphere);
}

void free_data_cylinder(t_data *data)
{
	t_cylinder *tmp;
	t_cylinder *tmp2;

	tmp = data->shape->cylinder->next;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	if (data->shape->cylinder)
		free(data->shape->cylinder);
}

void global_free(t_data *data)
{
	if (data->ambient_lightning)
		free(data->ambient_lightning);
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
	free_data_sphere(data);
	free_data_plane(data);
	free_data_cylinder(data);
	if (data->shape)
		free(data->shape);
}
