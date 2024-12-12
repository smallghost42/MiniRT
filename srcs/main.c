/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:49:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/12 15:54:05 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_scene(t_scene *scene)
{
	int	*_bpp;
	int	*_line_length;
	int	*_endian;

	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, "MINIRT");
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	_bpp = &(scene->bpp);
	_endian = &(scene->endian);
	_line_length = &(scene->line_length);
	scene->addr = mlx_get_data_addr(scene->img, _bpp, _line_length, _endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	(void)argc;
	(void)argv;
	init_scene(&scene);
	// t_vec3 *origin = vec3_create(10, 10, 0);
	// t_vec3 *direction = vec3_create(10, 0, 1);
	// t_ray *ray = ray_create(*origin, *direction);
	// t_vec3 *center = vec3_create(500, 300, 0);
	// draw_hit_sphere(*ray, *center, 50, &scene);
	 t_vec3 *camera_pos = vec3_create(0, 0, 0); // Camera at origin
    t_vec3 *sphere_center = vec3_create(0, 0, -5); // Sphere at z = -5
    float radius = 1.0;
// draw_sphere(500, 500, 100, &scene);
draw_sphere_0(&scene, *camera_pos, *sphere_center, radius);
    // Free memory
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	run_hook_cycle(scene);
	return (0);
}
