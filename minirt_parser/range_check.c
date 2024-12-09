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
	double value;

	value = 0.0;
	if (is_valid_float(str2[1], 1))
		return (1);
	value = ft_atof(str2[1]);
	if (value < 0.0 || value > 1.0)
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
