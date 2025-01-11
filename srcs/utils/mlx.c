/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:45:47 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/11 10:31:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_hit_pt(t_hit_pt* hit_pt)
{
	if (!hit_pt)
		return ;
	if (hit_pt->shape)
		free(hit_pt->shape);
	free(hit_pt);
	hit_pt = NULL;
}

void	my_mlx_pixel_put(t_scene *scene, float x, float y, int color)
{
	int		_x;
	int		_y;
	int		pixel_offset;
	char	*dst;

	_x = round(x);
	_y = round(y);
	if (_x >= 0 && _x < WIN_WIDTH)
	{
		if (_y >= 0 && _y < WIN_HEIGHT)
		{
			pixel_offset = _y * scene->line_length + _x * scene->bpp / 8;
			dst = scene->addr + pixel_offset;
			*(unsigned int *)dst = color;
		}
	}
}

static int	on_destroy(t_scene *scene)
{
	free_scene_data(scene->data);
	// free(scene->data);
	mlx_destroy_image(scene->mlx, scene->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	free_hit_pt(scene->hit_pt);
	exit(EXIT_SUCCESS);
}

static int	on_keydown(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
		on_destroy(scene);
	return (0);
}

void	run_hook_cycle(t_scene scene)
{
	mlx_hook(scene.win, 2, 1L << 0, on_keydown, &scene);
	mlx_hook(scene.win, 17, 0L, on_destroy, &scene);
	mlx_loop(scene.mlx);
}


void	print_direction()
{
	printf("-x to x: from left to right\n");
	printf("-y to y: from top to bottom\n");
	printf("-z to z: from the screen to the user\n");
}
