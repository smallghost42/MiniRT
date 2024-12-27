/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:56:40 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/27 13:15:44 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	p is hit point
	C is cylinder center
	V is normalized cylinder axis unit vector
	m is distance ||C - A|| such as (P - A).V = 0
	D is the ray direction
	t is the distance
	O is the camera position
	r is the rayon
	X = O - C
*/

// t_vec3 get_sphere_normal()
// {
// 	t_vec3	normal_vec;

// 	//normal = vec3_normalize(P - C - V * m);
// 	return (normal_vec);
// }

/*
	* To calculate distance, we have
		- a = D.D - (D.V)^2
		- c = X.X - (X.V)^2 - r^2
		- b = 2 * (D.X - (D.V) * (X.V))
	and we have then,
		x = (-b -/+ sqrt(delta)) / 2a  and delta = b^2 - 4ac;
	
	and for finite cylinder we have to calculate the height
		m = D.V*t + X.V  and check m is in 0, height
*/

float	get_cylinder_point_distance(t_ray ray, t_vec3 center, t_vec3 axis_vec, float diameter, float height)
{
	float	distance;
	float	discriminant;
	float	a, b, c, x1, x2, m;
	float	radius;
	t_vec3	x;

	radius = diameter / 2.0;
	x = vec3_substract(ray.origin, center);
	a = vec3_get_dot_product(ray.direction, ray.direction) - powf(vec3_get_dot_product(ray.direction, axis_vec), 2.0);
	c = vec3_get_dot_product(x,x) - powf(vec3_get_dot_product(x, axis_vec), 2.0) - powf(radius, 2.0);
	b = 2 * (vec3_get_dot_product(ray.direction, x) - (vec3_get_dot_product(ray.direction, axis_vec) * vec3_get_dot_product(x, axis_vec)));
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	discriminant = sqrt(discriminant);
	x1 = (-b - discriminant) / ( 2 * a);
	x2 = (-b + discriminant) / ( 2 * a);
	distance = fmax(x1, x2);
	if (distance < 0)
		return (-1);
	m = vec3_get_dot_product(ray.direction, vec3_const_multiply(axis_vec, distance)) + vec3_get_dot_product(x, axis_vec);
	if (m >= 0 && m <= height)
		return (distance);
	return (-1);
}

int render_cylinder(t_scene *scene, t_vec3 camera_pos, t_vec3 cylinder_center, t_vec3 axis_vec, float diameter, float height)
{
	int     coord[2]; //x, y
    float   image_plane_coord[2];
    float   fov_angle;
    float   current_distance;
    float   distance;
    t_ray   ray;
    t_vec3  normal_vec;

    coord[0] = 0;
    fov_angle = 70.0;
    distance = INFINITY;
    while (coord[0] < WIN_WIDTH)
    {
        coord[1] = 0;
        while (coord[1] < WIN_HEIGHT)
        {
            image_plane_coord[0] = get_x_image_plane(coord[0], fov_angle);
            image_plane_coord[1] = get_y_image_plane(coord[1], fov_angle);

            ray.direction = get_ray_direction(image_plane_coord);
            ray.origin = camera_pos;

			current_distance = get_cylinder_point_distance(ray, cylinder_center, axis_vec, diameter, height);
            if (current_distance >= 0)
            {
                if (distance > current_distance)
                    distance = current_distance;
				int color = get_color_from_trgb(1, 255, 0, 0);
                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
