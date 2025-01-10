/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:54:34 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/09 15:33:00 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float   get_aspect_ratio(void)
{
    return (WIN_WIDTH / WIN_HEIGHT);
}

float   get_x_projected(int x, int fov)
{
    float   aspect_ratio;
    float	x_image_plane;

    aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
    x_image_plane = (2.0f * (x + 0.5f) / WIN_WIDTH) - 1.0f;
    x_image_plane *= aspect_ratio * tan((PI * fov) / (180.0f * 2.0f));
    return (x_image_plane);
}

// float   get_y_projected(int y, int fov)
// {
//     float   aspect_ratio;
//     float	y_image_plane;

//     aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
// 	y_image_plane = 2.0f * (y + 0.5f) / WIN_HEIGHT - 1;
// 	// y_image_plane = 1 - 2.0f * (y + 0.5f) / WIN_HEIGHT;
// 	y_image_plane *= tan((PI * fov) / (180.0f * 2.0f));
// 	return (y_image_plane);
// }

//y ambany
float get_y_projected(int y, int fov)
{
    float aspect_ratio = (float)WIN_HEIGHT / WIN_WIDTH;
    float viewport_height = 2.0 * tan((fov * PI / 180.0) / 2.0);
    float viewport_width = viewport_height / aspect_ratio;

    return ((1.0 - 2.0 * (y/ (float)WIN_HEIGHT)) * viewport_height / 2.0);
}
