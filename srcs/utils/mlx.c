/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:45:47 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/15 11:02:48 by trazanad         ###   ########.fr       */
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

int	update_rendu(t_scene *scene, t_vec3 (*f)(t_vec3, float), float param)
{
	if (!scene->selected_obj)
		return (1);
	if (scene->selected_obj->sphere)
		scene->selected_obj->sphere->center = f(scene->selected_obj->sphere->center, param);
	else if (scene->selected_obj->cylinder)
		scene->selected_obj->cylinder->center = f(scene->selected_obj->cylinder->center, param);
	// else if (scene->selected_obj->plane)
	// 	scene->selected_obj->plane->color = 255;
	reset_img(scene);
}

int	translate_camera(t_scene *scene, t_vec3 (*f)(t_vec3, float), float param)
{
	if (scene->selected_obj->cylinder && scene->selected_obj->plane && scene->selected_obj->sphere)
		return (1);
	scene->data->camera->position = f(scene->data->camera->position, param);
	// else if (scene->selected_obj->plane)
	// 	scene->selected_obj->plane->color = 255;
	reset_img(scene);
	return (0);
}

int	rotate_camera(t_scene *scene, t_vec3 (*f)(t_vec3, float), float param)
{
	if (scene->selected_obj->cylinder && scene->selected_obj->plane && scene->selected_obj->sphere)
		return (1);
	scene->data->camera->orientation = f(scene->data->camera->orientation, param);
	// else if (scene->selected_obj->plane)
	// 	scene->selected_obj->plane->color = 255;
	reset_img(scene);
	return (0);
}

static int	on_destroy(t_scene *scene)
{
	free_hit_pt(scene->hit_pt);
	free(scene->selected_obj);
	free_scene_data(scene->data);
	// free(scene->data);
	mlx_destroy_image(scene->mlx, scene->img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
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
	else if (keycode == XK_c)
	{
		scene->selected_obj->cylinder = NULL;
		scene->selected_obj->sphere = NULL;
		scene->selected_obj->plane = NULL;
		scene->select_camera = 1;
	}
	else if (keycode == XK_Left)
	{
		if (scene->select_camera)
		translate_camera(scene, translate_x, -DELTA);
		update_rendu(scene, translate_x, -DELTA);
	}
	else if (keycode == XK_Right)
	{
		if (scene->select_camera)
		translate_camera(scene, translate_x, DELTA);
		update_rendu(scene, translate_x, DELTA);
	}
	else if (keycode == XK_Up)
	{
		if (scene->select_camera)
		translate_camera(scene, translate_y, -DELTA);
		update_rendu(scene, translate_y, -DELTA);
	}
	else if (keycode == XK_Down)
	{
		if (scene->select_camera)
		translate_camera(scene, translate_y, DELTA);
		update_rendu(scene, translate_y, DELTA);
	}
	else if (keycode == 65451)
	{
		if (scene->select_camera)
		translate_camera(scene, translate_z, DELTA);
		update_rendu(scene, translate_z, DELTA);
	}
	else if (keycode == 65453)
	{
		if (scene->select_camera)
		translate_camera(scene, translate_z, -DELTA);
		update_rendu(scene, translate_z, -DELTA);
	}
	else if (keycode == XK_x)
	{
		if (scene->select_camera)
		rotate_camera(scene, rotate_x, THETA);
		if (scene->selected_obj->cylinder)
		{
		scene->selected_obj->cylinder->orientation = rotate_x(scene->selected_obj->cylinder->orientation, THETA);
		reset_img(scene);
		}
	}
	else if (keycode == XK_y)
	{
		if (scene->select_camera)
		rotate_camera(scene, rotate_y, THETA);
		if (scene->selected_obj->cylinder)
		{
		scene->selected_obj->cylinder->orientation = rotate_y(scene->selected_obj->cylinder->orientation, THETA);
		reset_img(scene);
		}
	}
	else if (keycode == XK_z)
	{
		if (scene->select_camera)
		rotate_camera(scene, rotate_z, THETA);
		if (scene->selected_obj->cylinder)
		{
		scene->selected_obj->cylinder->orientation = rotate_z(scene->selected_obj->cylinder->orientation, THETA);
		reset_img(scene);
		}
	}
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
