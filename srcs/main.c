/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:49:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/27 16:33:00 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_scene *scene)
{
	int	*_bpp;
	int	*_line_length;
	int	*_endian;

	scene->data = NULL; //////////////////
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (1);
	scene->win = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, "MINIRT");
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	_bpp = &(scene->bpp);
	_endian = &(scene->endian);
	_line_length = &(scene->line_length);
	scene->addr = mlx_get_data_addr(scene->img, _bpp, _line_length, _endian);
	return (0);
}

int	add_data(int argc, char **argv, t_scene *scene)
{
	t_data	*data;
	int		is_error_in_parsing;	

	if (argc != 2)
	{
		ft_putstr_fd("Error: invalid number of argument!\n", 2);
		exit(EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	is_error_in_parsing = parse_file(argv[1], data);
	if (is_error_in_parsing)
	{
		free_scene_data(data);
		free(data);
		ft_putstr_fd("Error: invalid file input!\n", 2);
		exit(EXIT_FAILURE);
	}
	scene->data = data;
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	//add_data(argc, argv, &scene);
	mute_arg(argc, argv);
	init_mlx(&scene);
	print_direction();
	draw_some_plane(&scene);
	// draw_some_sphere(&scene);
	draw_some_cylinder(&scene);
    // Free memory
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	run_hook_cycle(scene);
	return (0);
}
