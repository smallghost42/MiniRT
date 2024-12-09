/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb_normaliser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:46:25 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:46:33 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		return (1);
	return (0);
}

int check_valid_coordinate(char *cord)
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
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int check_3dnormaliser(char *cord)
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
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}
