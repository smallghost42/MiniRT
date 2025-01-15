/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:31:05 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/15 12:06:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"

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

    tmp = vec3_scalar_mult(ray.direction, ray_param);
    vector = vec3_add(ray.origin, tmp);
    return (vector);
}

t_vec3  get_ray_direction(float coord[2])
{
    t_vec3  camera_orientation;
    t_vec3  ray_direction;
    t_vec3  camera_right;
    t_vec3  camera_up;

    // ray_direction = vec3_create(coord[0], coord[1], -1);
    camera_orientation = vec3_normalize(vec3_create(0, 0, -1));
    camera_right = vec3_normalize(vec3_cross_product(vec3_create(0, 1, 0), camera_orientation));
    camera_up = vec3_normalize(vec3_cross_product(camera_orientation, camera_right));
    ray_direction = vec3_add(
        vec3_add(
            vec3_scalar_mult(camera_right, -coord[0]),
            vec3_scalar_mult(camera_up, -coord[1])
        ),
        camera_orientation
    );
    return (vec3_normalize(ray_direction));
}

t_vec3  get_ray_direction0(float coord[2], t_camera *camera)
{
    t_vec3  ray_direction;
    t_vec3  camera_right;
    t_vec3  camera_up;

    // ray_direction = vec3_create(coord[0], coord[1], -1);
    camera->orientation = vec3_normalize(camera->orientation);
    camera_right = vec3_normalize(vec3_cross_product(vec3_create(0, 1, 0), camera->orientation));
    camera_up = vec3_normalize(vec3_cross_product(camera->orientation, camera_right));
    ray_direction = vec3_add(
        vec3_add(
            vec3_scalar_mult(camera_right, -coord[0]),
            vec3_scalar_mult(camera_up, -coord[1])
        ),
        camera->orientation
    );
    return (vec3_normalize(ray_direction));
}
