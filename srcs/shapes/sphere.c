/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:46:11 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/12 14:23:10 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int draw_sphere(int x, int y, int radius, t_scene *scene)
{
    int i;
    int j;
    int _x;
    int _y;

    i = 0;
    while (i <= 2 * radius)
    {
        j = 0;
        _x = i - radius;
        while (j <= 2 * radius)
        {
            _y = j - radius;
            if (_x * _x + _y * _y <= radius * radius)
                my_mlx_pixel_put(scene, _x + x, _y + y, COLOR);
            j++;
        }
        i++;
    }
    return (0);
}
