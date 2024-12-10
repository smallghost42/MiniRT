/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check_elem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 07:25:29 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/10 07:41:23 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int valid_range_sphere(char **str2)
{
	double diameter;

	diameter = 0.0;
	if (check_valid_coordinate(str2[1]))
		return (1);
	if (is_valid_float(str2[2], 1))
		return (1);
	diameter = ft_atof(str2[2]);
	if (check_valid_rgb(str2[3]))
		return (1);
	return (0);
}
