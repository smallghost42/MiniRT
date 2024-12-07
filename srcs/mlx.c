/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:45:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/07 11:00:08 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_mlx_pixel_put(t_scene *scene, float x, float y, int color)
{
	int		real_x;
	int		real_y;
	char	*dst;

	real_x = round(x);
	real_y = round(y);
	if (real_x >= 0 && real_x < WIN_WIDTH)
	{
		if (real_y >= 0 && real_y < WIN_HEIGHT)
		{
			dst = scene->addr + (real_y * scene->line_length + real_x * (scene->bpp / 8));
			*(unsigned int *)dst = color;
		}
	}
}

static int	on_destroy(t_scene *scene)
{
	//clear map;
	mlx_destroy_image(scene->mlx, scene->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	exit(EXIT_SUCCESS);
}

static int	on_keydown(int keycode, t_scene *scene)
{
	if (keycode == 65307)
		on_destroy(scene);
	return (0);
}

void	hook_loop(t_scene scene)
{
	mlx_hook(scene.win, 2, 1L << 0, on_keydown, &scene);
	mlx_hook(scene.win, 17, 0L, on_destroy, &scene);
	mlx_loop(scene.mlx);
}
