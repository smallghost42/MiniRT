/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check_elem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 07:25:29 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/23 11:28:04 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int valid_range_sphere(char **str2, t_data *data)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	if (check_valid_coordinate(str2[1], &sphere->center))
		return (1);
	if (is_valid_float(str2[2], 2))
		return (1);
	sphere->diameter = ft_atof(str2[2]);
	if (check_valid_rgb(str2[3]))
		return (1);
	// sphere->color = ;
	sphere->next = NULL;
	if (data->shape->sphere)
		add_back_sphere(&(data->shape->sphere), sphere);
	else
		data->shape->sphere = sphere;
	return (0);
}

int valid_range_plane(char **str2, t_data *data)
{
	t_plane *plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (1);
	if (check_valid_coordinate(str2[1], &plane->center))
		return (1);
	if (check_3dnormaliser(str2[2], &plane->orientation))
		return (1);
	if (check_valid_rgb(str2[3]))
		return (1);
	// plane->color = ;
	plane->next = NULL;
	if (data->shape->plane)
		add_back_plane(&(data->shape->plane), plane);
	else
		data->shape->plane = plane;
	return (0);
}

int valid_range_cylinder(char **str2, t_data *data)
{
	t_cylinder *cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	if (check_valid_coordinate(str2[1], &cylinder->center))
		return (1);
	if (check_3dnormaliser(str2[2], &cylinder->orientation))
		return (1);
	if (is_valid_float(str2[3], 2))
		return (1);
	cylinder->diameter = ft_atof(str2[3]);
	if (is_valid_float(str2[4], 2))
		return (1);
	cylinder->height = ft_atof(str2[4]);
	if (check_valid_rgb(str2[5]))
		return (1);
	// cylinder->color = ;
	cylinder->next = NULL;
	if (data->shape->cylinder)
		add_back_cylinder(&(data->shape->cylinder), cylinder);
	else
		data->shape->cylinder = cylinder;
	return (0);
}
