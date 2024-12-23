/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:40:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 14:07:11 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	mute_arg(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	draw_some_sphere(t_scene *scene)
{
	t_vec3 camera_pos = vec3_create(0, 0, 5000);      
	t_vec3 sphere_center = vec3_create(2500, 0, -500);
	float radius = 1000.0;                        

	render_sphere(scene, camera_pos, sphere_center, radius);
	// t_vec3 *camera_pos0 = vec3_create(0, 0, 0);
	// t_vec3 *sphere_center0 = vec3_create(0, 10, -20);    
	// float radius0 = 5.0;                                 
	// draw_sphere_0(&scene, *camera_pos0, *sphere_center, radius0);
}
