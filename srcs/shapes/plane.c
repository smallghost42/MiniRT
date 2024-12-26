/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:29:59 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/26 17:01:33 by trazanad         ###   ########.fr       */
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
				int color = get_color_from_trgb(1, 0, 255, 255);
                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}


// float get_plane_point_distance(t_ray ray, t_vec3 plane_point, t_vec3 plane_normal)
// {
//     float denominator = vec3_get_dot_product(plane_normal, ray.direction);
    
//     // Check if ray is parallel to plane
//     // if (fabs(denominator) < EPSILON)
//     //     return -1;
        
//     t_vec3 camera_to_point = vec3_substract(plane_point, ray.origin);
//     float distance = vec3_get_dot_product(plane_normal, camera_to_point) / denominator;
    
//     return (distance);
// }

// int render_plane(t_scene *scene, t_vec3 camera_pos, t_vec3 plane_point, t_vec3 plane_normal)
// {
//     int coord[2];  // x, y coordinates
//     float image_plane_coord[2];
//     float fov_angle;
//     float current_distance;
//     t_ray ray;
//     const float MAX_RENDER_DISTANCE = 1000.0f;
    
//     coord[0] = 0;
//     fov_angle = 70.0;
    
//     while (coord[0] < WIN_WIDTH)
//     {
//         coord[1] = 0;
//         while (coord[1] < WIN_HEIGHT)
//         {
//             // Convert screen coordinates to image plane coordinates
//             image_plane_coord[0] = get_x_image_plane(coord[0], fov_angle);
//             image_plane_coord[1] = get_y_image_plane(coord[1], fov_angle);
            
//             // Setup ray
//             ray.direction = get_ray_direction(image_plane_coord);
//             ray.origin = camera_pos;
            
//             // Get intersection distance
//             current_distance = get_plane_point_distance(ray, plane_point, plane_normal);
            
//             // If we have a valid intersection
//             if (current_distance >= 0 )
//             {
//                 // Calculate color intensity based on distance
//                 // int intensity = (int)(255 * (1 - current_distance/MAX_RENDER_DISTANCE));
//                 // intensity = intensity < 0 ? 0 : intensity > 255 ? 255 : intensity;
                
//                 // Create yellow color with distance-based intensity
//                 int color = get_color_from_trgb(1, 255, 255, 0);
                
//                 // Draw pixel
//                 my_mlx_pixel_put(scene, coord[0], coord[1], color);
//             }
            
//             coord[1]++;
//         }
//         coord[0]++;
//     }
    
//     return (0);
// }