/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:29:59 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/27 15:53:09 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_plane_point_distance(t_ray ray, t_vec3 plane_point, t_vec3 plane_normal)
{
	float	distance;
	t_vec3	camera_to_point;

	camera_to_point = vec3_substract(plane_point, ray.origin);
	distance = vec3_get_dot_product(plane_normal, camera_to_point) / vec3_get_dot_product(plane_normal, ray.direction);
	return (distance);
}

static int get_diffuse_light_color(t_ray ray, float distance, t_vec3 normal_vec)
{
    float   brightness;
    int     color;
    int     trgb[4];

	//calculate hit point to light vec
    t_vec3 light_pos = vec3_create(0, 100, 0);
	t_vec3 point_to_light_vec = get_point_to_light_vector(light_pos, ray, distance);
    brightness = fmax(vec3_get_dot_product(normal_vec, point_to_light_vec), 0.1);
    trgb[0] = 1;
    trgb[1] = roundf(10 * brightness);
    trgb[2] = roundf(50 * brightness);
    trgb[3] = roundf(60 * brightness);
    color = get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
    return (color);
}

int render_plane(t_scene *scene, t_vec3 camera_pos, t_vec3 plane_point, t_vec3 plane_normal)
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

            current_distance = get_plane_point_distance(ray, plane_point, plane_normal);
            if (current_distance >= 0)
            {
                if (distance > current_distance)
                    distance = current_distance;
				// int color = get_color_from_trgb(1, 0, 255, 255);
				int color = get_diffuse_light_color(ray, current_distance, plane_normal);

                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
