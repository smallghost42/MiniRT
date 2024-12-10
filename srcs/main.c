/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:49:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/09 10:25:06 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_scene(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, "MINIRT");
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->addr = mlx_get_data_addr(scene->img, &(scene->bpp), &(scene->line_length), &(scene->endian));
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	(void)argc;
	(void)argv;
	init_scene(&scene);
	draw_sphere(WIN_WIDTH / 2, WIN_HEIGHT / 2, 400, &scene);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	hook_loop(scene);
	return (0);
}
