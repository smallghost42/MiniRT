/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:31:05 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 13:48:50 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

/*
    - No transformation is yet applied to these calcul (no FOV transformation, projection, center translation)
*/

//change origin and direction to
t_ray   *ray_allocate(t_vec3 origin, t_vec3 direction)
{
    t_ray   *ray;

    ray = malloc(sizeof(t_ray));
    if (!ray)
        return (NULL);
    ray->origin = origin;
    ray->direction = direction;
    return (ray);
}

t_ray   ray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray   ray;

    ray.origin = origin;
    ray.direction = direction;
    return (ray);
}

t_vec3  get_intersection(t_ray ray, float ray_param)
{
    t_vec3  vector;
    t_vec3  tmp;

    tmp = vec3_const_multiply(ray.direction, ray_param);
    vector = vec3_add(ray.origin, tmp);
    return (vector);
}

int is_ray_hitting_sphere(t_ray ray, t_vec3 center, float radius)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;

    oc = vec3_substract(center, ray.origin);
    a = vec3_get_dot_product(ray.direction, ray.direction);
    b = 2 * vec3_get_dot_product(oc, ray.direction);
    c = vec3_get_dot_product(oc, oc) - radius * radius;
    return ((b * b - 4 * a * c) >= 0);
}

int draw_sphere_by_ray(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius) {
    int x, y;
    float screen_x, screen_y;
    float aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
    t_ray   ray;
    t_vec3  ray_direction;

    for (y = 0; y < WIN_HEIGHT; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
           screen_x = get_x_image_plane(x, 90, aspect_ratio);
            screen_y = get_y_image_plane(y, 90, aspect_ratio);
            ray_direction = vec3_create(screen_x, screen_y, -1);
            ray = ray_create(camera_pos, vec3_normalize(ray_direction));
            if (is_ray_hitting_sphere(ray, sphere_center, radius)) {
                my_mlx_pixel_put(scene, x, y, COLOR);
            }
        }
    }
    return 0;
}



