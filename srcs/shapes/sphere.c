/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:56:33 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/12 13:02:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float   sphere_ray_hit_distance(t_ray ray, t_vec3 center, float radius)
{
    t_vec3  oc;
    float   x[2];
    float   quadratic_params[5]; //a, b, c , discriminant, root of discriminant

    oc = vec3_substract(center, ray.origin);
    quadratic_params[0] = vec3_dot_product(ray.direction, ray.direction);
    quadratic_params[1] = -2.0 * vec3_dot_product(oc, ray.direction);
    quadratic_params[2] = vec3_dot_product(oc, oc) - (radius * radius);
    static int p = 1;
    quadratic_params[3] = quadratic_params[1] * quadratic_params[1];
    quadratic_params[3] -= 4.0 * quadratic_params[0] * quadratic_params[2];
    if (quadratic_params[3] < 0)
        return (-1);
    if (quadratic_params[3] == 0)
        return (-quadratic_params[1] / (2.0 * quadratic_params[0]));
    quadratic_params[4] = sqrt(quadratic_params[3]);
    x[0] = -quadratic_params[1] - quadratic_params[4];
    x[1] = -quadratic_params[1] + quadratic_params[4];
    if (x[0] > 0) 
        return (x[0] / (2.0 * quadratic_params[0]));
    else if (x[1] > 0)
        return (x[1] / (2.0 * quadratic_params[0]));
    return (-1);
}

t_vec3  sphere_normal_vec(t_ray ray, float distance, t_sphere* sphere)
{
    t_vec3  intersected_pt;

    intersected_pt = ray_intersection_pt(ray, distance);
    return (vec3_normalize(vec3_substract(intersected_pt, sphere->center)));
}
