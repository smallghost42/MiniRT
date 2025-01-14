/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:45:47 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/14 14:39:54 by trazanad         ###   ########.fr       */
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

void	reset_img(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img);
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->addr = mlx_get_data_addr(scene->img, &(scene->bpp), &(scene->line_length), &(scene->endian));
	render_scene(scene);//transformation and display
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img, 0, 0);
}

int	update_rendu(t_scene *scene, t_vec3 (*f)(t_vec3))
{
	// if (!(*hit_pt))
	// 	return (1);
	// else if ((*hit_pt)->shape->plane)
	// 	return (0);
	// reset_img(scene);
}

static int	on_destroy(t_scene *scene)
{
	print_data(scene->data);
	free_scene_data(scene->data);
	// free(scene->data);
	mlx_destroy_image(scene->mlx, scene->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	free_hit_pt(scene->hit_pt);
	exit(EXIT_SUCCESS);
}

int mouse_hook(int button, int x, int y, void *param) 
{
    // (void)param;
    // printf("Mouse clicked: Button %d at (%d, %d)\n", button, x, y);
	select_object(x, y, (t_scene *)param);
	reset_img((t_scene *)param);
    return (0);
}

static int	on_keydown(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
		on_destroy(scene);
	// else if (keycode == XK_Left)
	// else if (keycode == XK_Right)
		// update_rendu(hit_pt, translate_x);
	// else if (keycode == XK_Up)
	// else if (keycode == XK_Down)
	// else if (keycode == XK_plus)
	// else if (keycode == XK_minus)
	// print_data(scene->data);
	return (0);
}

void	run_hook_cycle(t_scene scene)
{
	mlx_mouse_hook(scene.win, mouse_hook, &scene);
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
