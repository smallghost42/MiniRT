/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:54:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/18 08:04:28 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float   get_aspect_ratio(void)
{
    return (WIN_WIDTH / WIN_HEIGHT);
}

float   get_x_image_plane(int x, int fov, float aspect_ratio)
{
    float	x_image_plane;

    x_image_plane = (2.0f * (x + 0.5f) / WIN_WIDTH) - 1.0f;
    x_image_plane *= aspect_ratio * tan((PI * fov) / (180.0f * 2.0f));
    return (x_image_plane);
}

float   get_y_image_plane(int y, int fov, float aspect_ratio)
{
    float	y_image_plane;

	y_image_plane = 1 - 2.0f * (y + 0.5f) / WIN_HEIGHT;
	y_image_plane *= tan((PI * fov) / (180.0f * 2.0f));
	return (y_image_plane);
}
