/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:46:11 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/09 09:19:18 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int draw_sphere(int x, int y, int radius, t_scene *scene)
{
    int i;
    int j;
    int x0;
    int y0;

    i = 0;
    while (i <= 2 * radius)
    {
        j = 0;
        x0 = i - radius;
        while (j <= 2 * radius)
        {
            y0 = j - radius;
            if (x0 * x0 + y0 * y0 <= radius * radius)
                int_mlx_pixel_put(scene, x0 + x, y0 + y, COLOR);
            j++;
        }
        i++;
    }
    return (0);
}

int draw_plane(int x, int y, t_scene *scene)
{
    int i;
    int j;

    i = 0;
    while (i <= x)
    {
        j = 0;
        while (j <= y)
        {
            int_mlx_pixel_put(scene, i , j, COLOR);
            // ft_printf("%d, %d\n" , i, j);
            j++;
        }
        i++;
    }
    return (0);
}
