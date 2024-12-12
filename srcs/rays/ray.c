/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:31:05 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/12 14:40:22 by trazanad         ###   ########.fr       */
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
    t_vec3  *oc;
    float   disciminant;
    float   quadratic_params[3];

    oc = vec3_substract(center, ray.origin);
    quadratic_params[0] = vec3_get_dot_product(ray.direction, ray.direction);
    quadratic_params[1] = -2 * vec3_get_dot_product(ray.direction, *oc);
    quadratic_params[2] = vec3_get_dot_product(*oc, *oc) - radius * radius;
    disciminant = quadratic_params[1] * quadratic_params[1];
    printf("%f %f %f\n", quadratic_params[0], quadratic_params[1], quadratic_params[2]);
    disciminant -= 4 * quadratic_params[0] * quadratic_params[2];
    return (disciminant >= 0);
}

