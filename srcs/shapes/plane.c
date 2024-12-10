/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:29:59 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/10 08:30:14 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
