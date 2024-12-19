/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:03:33 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/12 08:22:35 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_trgb_from_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	*get_color_from_trgb(int color)
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
