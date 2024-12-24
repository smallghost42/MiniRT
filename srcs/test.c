/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:40:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/24 15:13:42 by trazanad         ###   ########.fr       */
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
	// t_vec3 camera_pos = vec3_create(0, 0, 5000);
	t_vec3 camera_pos = vec3_create(0.0,0, 50);      
	t_vec3 sphere_center = vec3_create(0.0,0.0, -20.6);
	float radius = 12.6;                        

	render_sphere(scene, camera_pos, sphere_center, radius);
	sphere_center = vec3_create(20, 10, -50);    
	radius = 10.0;                                 
	render_sphere(scene, camera_pos, sphere_center, radius);
	sphere_center = vec3_create(-50, -50, -50);    
	radius = 10.0;                                 
	render_sphere(scene, camera_pos, sphere_center, radius);
	sphere_center = vec3_create(-50, 50, -150);    
	radius = 10.0;                                 
	render_sphere(scene, camera_pos, sphere_center, radius);
	sphere_center = vec3_create(50, -50, -100);    
	radius = 10.0;                                 
	render_sphere(scene, camera_pos, sphere_center, radius);
}
