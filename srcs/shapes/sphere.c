/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:46:11 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/24 14:50:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float get_sphere_pt_distance(t_ray ray, t_vec3 center, float radius)
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

static float is_pixel_visible(float coord[2], t_vec3 camera_pos, t_vec3 sphere_center, float radius)
{
    t_ray   ray;
    t_vec3  ray_direction;

    ray_direction = vec3_create(coord[0], coord[1], -1); // replace by camera orientation vec
    ray = ray_create(camera_pos, vec3_normalize(ray_direction));
    return (get_sphere_pt_distance(ray, sphere_center, radius));
}

t_vec3 get_sphere_normal(t_ray ray, float distance, t_vec3 sphere_center)
{
    t_vec3 hit_point;
    t_vec3 normal_vec;

    // Calculate the hit point
    hit_point = vec3_add(ray.origin, vec3_const_multiply(ray.direction, distance));

    // Calculate the normal vector
    normal_vec = vec3_substract(hit_point, sphere_center);
    normal_vec = vec3_normalize(normal_vec);

    return (normal_vec);
}


int render_sphere(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius)
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
            // Map pixel to image plane
            image_plane_coord[0] = get_x_image_plane(coord[0], fov_angle);
            image_plane_coord[1] = get_y_image_plane(coord[1], fov_angle);

            ray.direction = get_ray_direction(image_plane_coord);
            ray.origin = camera_pos;

            current_distance = get_sphere_pt_distance(ray, sphere_center, radius);
            if (current_distance >= 0)
            {
                distance = current_distance;
                normal_vec = get_sphere_normal(ray, current_distance, sphere_center);

                // Apply shading (example: dot product with light direction)
                float brightness = fmax(vec3_get_dot_product(normal_vec, vec3_create(0, 0, -1)), 0.0);
                int color = (int)(get_color_from_trgb(1, brightness * 5, brightness * 255, brightness * 255));
                //calculate color
                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
