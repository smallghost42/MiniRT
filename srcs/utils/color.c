/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:03:33 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/24 14:42:35 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color_from_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	*get_trgb_from_color(int color)
{
	int	*trgb;

	trgb = malloc(sizeof(int) * 4);
	if (!trgb)
		return (0);
	trgb[0] = (color >> 24) & 0xFF;
	trgb[1] = (color >> 16) & 0xFF;
	trgb[2] = (color >> 8) & 0xFF;
	trgb[3] = color & 0xFF;
	return (trgb);
}

// int	get_color_from_trgb0(int color)
// {
// 	int	trgb[4];

// 	trgb[0] = (color >> 24) & 0xFF;
// 	trgb[1] = (color >> 16) & 0xFF;
// 	trgb[2] = (color >> 8) & 0xFF;
// 	trgb[3] = color & 0xFF;
// 	return (trgb);
// }

int	get_color_from_normalized_value(float trgb[4])
{
	int	real_trgb[4];
	int	color;

	real_trgb[0] = 1; 
	real_trgb[1] = roundf(trgb[1] * 255);
	real_trgb[2] = roundf(trgb[2] * 255);
	real_trgb[3] = roundf(trgb[3] * 255);
	color = get_color_from_trgb(real_trgb[0], real_trgb[1], real_trgb[2], real_trgb[3]);
	return (color);
}

