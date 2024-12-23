/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:46:11 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 15:49:58 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int get_sphere_pt_distance(t_ray ray, t_vec3 center, float radius)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;
    float   distance;
    float   discriminant;
    
    oc = vec3_substract(center, ray.origin);
    a = vec3_get_dot_product(ray.direction, ray.direction);
    b = -2 * vec3_get_dot_product(oc, ray.direction);
    c = vec3_get_dot_product(oc, oc) - radius * radius;
    discriminant = b * b - (4 * a * c);
    if (discriminant < 0)
        return (-1);
    discriminant = sqrt(discriminant);
    distance = fmax((- b - discriminant) / (2 * a), (- b + discriminant) / (2 * a));
    return (distance);
}

static int is_pixel_visible(float coord[2], t_vec3 camera_pos, t_vec3 sphere_center, float radius)
{
    t_ray   ray;
    t_vec3  ray_direction;

    ray_direction = vec3_create(coord[0], coord[1], -1);
    ray = ray_create(camera_pos, vec3_normalize(ray_direction));
    return (get_sphere_pt_distance(ray, sphere_center, radius) >= 0);
}

int render_sphere(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius)
{
    int     coord[2]; //x, y
    float   image_plane_coord[2];
    float   fov_angle;

    coord[0] = 0;
    fov_angle = 90.0;
    while (coord[0] < WIN_WIDTH)
    {
        coord[1] = 0;
        while (coord[1] < WIN_HEIGHT)
        {
            image_plane_coord[0] = get_x_image_plane(coord[0], fov_angle);
            image_plane_coord[1] = get_y_image_plane(coord[1], fov_angle);
            if (is_pixel_visible(image_plane_coord, camera_pos, sphere_center, radius))
                my_mlx_pixel_put(scene, coord[0], coord[1], COLOR);
            coord[1] = coord[1] + 1;
        }
        coord[0] = coord[0] + 1;
    }
    return (0);
}
