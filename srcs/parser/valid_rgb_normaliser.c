/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb_normaliser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:46:25 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/23 11:28:11 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int check_valid_rgb(char *color)
{
	char **rgb;
	int i;

	i = 0;
	rgb = ft_split(color, ',');
	if (!rgb)
		return (1);
	while (rgb[i])
	{
		if (ft_valid_int(rgb[i]) || ft_atoi(rgb[i]) < 0 ||
			ft_atoi(rgb[i]) > 255)
		{
			free_split(rgb);
			return (1);
		}
		i++;
	}
	if (i != 3)
	{
		free_split(rgb);
		return (1);
	}
	free_split(rgb);
	return (0);
}

int check_valid_coordinate(char *cord, t_vec3 *vec3)
{
	char **cord2;
	int i;

	i = 0;
	cord2 = ft_split(cord, ',');
	if (!cord2)
		return (1);
	while (cord2[i])
	{
		if (is_valid_float(cord2[i], 1))
		{
			free_split(cord2);
			return (1);
		}
		vec3->x = ft_atof(cord2[0]);
		vec3->y = ft_atof(cord2[1]);
		vec3->z = ft_atof(cord2[2]);
		i++;
	}
	if (i != 3)
	{
		free_split(cord2);
		return (1);
	}
	free_split(cord2);
	return (0);
}

int check_3dnormaliser(char *cord, t_vec3 *vec3)
{
	char **coord;
	int i;

	i = 0;
	coord = ft_split(cord, ',');
	if (!cord)
		return (1);
	while (coord[i])
	{
		if (is_valid_float(coord[i], 1) || ft_atof(coord[i]) < -1.0 ||
			ft_atof(coord[i]) > 1.0)
		{
			free_split(coord);
			return (1);
		}
		vec3->x = ft_atof(coord[0]);
		vec3->y = ft_atof(coord[1]);
		vec3->z = ft_atof(coord[2]);
		i++;
	}
	if (i != 3)
	{
		free_split(coord);
		return (1);
	}
	free_split(coord);
	return (0);
}
