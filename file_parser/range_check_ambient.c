/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check_ambient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:18:47 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:00:54 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int valid_range_ambient(char **str2)
{
	double value;

	value = 0.0;
	if (is_valid_float(str2[1]))
		return (1);
	value = ft_atof(str2[1]);
	// check_valid_rgb();
	return (0);
}
