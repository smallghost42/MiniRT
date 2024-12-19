/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:31:05 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/19 09:13:35 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"
/*
    - No transformation is yet applied to these calcul (no FOV transformation, projection, center translation)
*/

//change origin and direction to
t_ray   *ray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray   *ray;

    ray = malloc(sizeof(t_ray));
    if (!ray)
        return (NULL);
    ray->origin = origin;
    ray->direction = direction;
    return (ray);
}

t_vec3  *get_intersection(t_ray ray, float ray_param)
{
    t_vec3  *vector;
    t_vec3  *tmp;

    tmp = vec3_const_multiply(ray.direction, ray_param);
    vector = vec3_add(ray.origin, *tmp);
    free(tmp);
    return (vector);
}

int is_ray_hitting_sphere(t_ray ray, t_vec3 center, float radius)
{
    t_vec3  *oc; // Vector from sphere center to ray origin
    float   a;   // dot(ray.direction, ray.direction)
    float   b;   // 2 * dot(oc, ray.direction)
    float   c;   // dot(oc, oc) - radius^2

    // Calculate vector OC (ray.origin - center)
    // oc = vec3_substract(ray.origin, center);
    oc = vec3_substract(center, ray.origin);

    // Coefficients of the quadratic equation
    a = vec3_get_dot_product(ray.direction, ray.direction);
    b = 2 * vec3_get_dot_product(*oc, ray.direction);
    c = vec3_get_dot_product(*oc, *oc) - radius * radius;

    // Free dynamically allocated memory
    free(oc);

    // Calculate discriminant

    // Return whether discriminant is non-negative
    return ((b * b - 4 * a * c) >= 0);
}

int draw_sphere_0(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius) {
    int x, y;
    float screen_x, screen_y; // Normalized screen coordinates
    float aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
    float fov = tan((PI / 180.0f) * 70.0f / 2); // Field of view, 70 degrees
    t_ray *ray;
    t_vec3 *tmp;

    for (y = 0; y < WIN_HEIGHT; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
            // Map pixel to normalized screen coordinates with aspect ratio correction
           screen_x = get_x_image_plane(x, 90, aspect_ratio);
            screen_y = get_y_image_plane(y, 90, aspect_ratio);
            // Set up the ray
            tmp = vec3_create(screen_x, screen_y, -1); // Assuming camera looks in -Z
            // Normalize the direction vector
                         // Normalize
             // Normalize
            float norm = vec3_get_norm(*tmp);  // Get the magnitude (norm)
             if (norm > 0) {  // Prevent division by zero
                tmp = vec3_const_multiply(*tmp, 1 / norm);  // Normalize by dividing by norm
            }
             ray = ray_create(camera_pos, *tmp);
            // Test for intersection with sphere
            if (is_ray_hitting_sphere(*ray, sphere_center, radius)) {
                // Draw pixel on intersection
                my_mlx_pixel_put(scene, x, y, COLOR);
            }
        }
    }

    return 0;
}



