/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check_ambient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:18:47 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:46:39 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int valid_range_ambient(char **str2)
{
	double ambient_light;

	ambient_light = 0.0;
	if (is_valid_float(str2[1], 1))
		return (1);
	ambient_light = ft_atof(str2[1]);
	if (ambient_light < 0.0 || ambient_light > 1.0)
		return (1);
	if (check_valid_rgb(str2[2]))
		return (1);
	return (0);
}

int valid_range_camera(char **str2)
{
	if (check_valid_coordinate(str2[1]))
		return (1);
	if (check_3dnormaliser(str2[2]))
		return (1);
	if (ft_valid_int(str2[3]) || ft_atoi(str2[3]) < 0 || ft_atoi(str2[3]) > 180)
		return (1);
	return (0);
}

int valid_range_light(char **str2)
{
	double light_brightness;

	light_brightness = 0.0;
	if (check_valid_coordinate(str2[1]))
		return (1);
	if (is_valid_float(str2[2], 1))
		return (1);
	light_brightness = ft_atof(str2[2]);
	if (light_brightness < 0.0 || light_brightness > 1.0)
		return (1);
	if (check_valid_rgb(str2[3])) // for bonus only
		return (1);
	return (0);
}
