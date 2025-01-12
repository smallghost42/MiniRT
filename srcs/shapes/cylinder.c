/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:42:11 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/12 13:16:08 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float   quadratic_solution(float params[5], t_vec3 vec[3], t_ray ray, float h)
{
    float   tmp;
    float   x[2];
    float   m[2];
    float   distance;

    distance = -1;
    tmp = vec3_dot_product(vec[2], vec[1]);
    x[0] = (-params[1] - params[4]) / (2.0 * params[0]);
    x[1] = (-params[1] + params[4]) / (2.0 * params[0]);
    m[0] = vec3_dot_product(ray.direction, vec3_scalar_mult(vec[1], x[0]));
    m[0] += tmp;
    m[1] = vec3_dot_product(ray.direction, vec3_scalar_mult(vec[1], x[1]));
    m[1] += tmp;
    if (x[0] > 0 && m[0] >= -h &&  m[0] <= h)
        distance = x[0];
    // else if (x[1] > 0 && m[1] >= -h &&  m[1] <= h)
    // {
    //     if (distance < 0 || x[1] < distance)
    //         distance = x[1];
    // }
    if (x[1] > 0 && m[1] >= -h &&  m[1] <= h)
    {
        if (distance < 0 || x[1] < distance)
            distance = x[1];
    }
    if (distance < 0)
        return (-1);
    return (distance);
}

float   cylinder_quadratic(t_vec3 vec[2], float  params[2], t_ray ray)
{
    t_vec3  oc;
    t_vec3  q_params[3];
    float   distance;
    float   quadratic_params[5]; //a, b, c , discriminant, root of discriminant

    oc = vec3_substract(ray.origin, vec[0]);
    // oc = vec3_substract(vec[0], ray.origin);
    quadratic_params[0] = vec3_dot_product(ray.direction, ray.direction);
    quadratic_params[0] -= powf(vec3_dot_product(ray.direction, vec[1]), 2.0);
    quadratic_params[1] = vec3_dot_product(ray.direction, vec[1]);
    quadratic_params[1] *= vec3_dot_product(oc, vec[1]);
    quadratic_params[1] -= vec3_dot_product(ray.direction, oc);
    quadratic_params[1] *= -2;
    quadratic_params[2] = vec3_dot_product(oc, oc) - (params[0] * params[0]);
    quadratic_params[2] -= powf(vec3_dot_product(oc, vec[1]), 2.0);
    quadratic_params[3] = quadratic_params[1] * quadratic_params[1];
    quadratic_params[3] -= 4.0 * quadratic_params[0] * quadratic_params[2];
    if (quadratic_params[3] < 0)
        return (-1);
    quadratic_params[4] = sqrt(quadratic_params[3]);
    q_params[0] = vec[0];
    q_params[1] = vec[1];
    q_params[2] = oc;
    distance = quadratic_solution(quadratic_params, q_params, ray, params[1]);
    return (distance);
}

float   cylinder_ray_hit_distance(t_ray ray, t_cylinder* cylinder)
{
    float   distance;
    t_vec3  cylinder_vec[2]; //center, axis_vec
    float   cylinder_params[2]; //radius, height

    cylinder_vec[0] = cylinder->center;
    cylinder_vec[1] = cylinder->orientation;
    cylinder_params[0] = cylinder->diameter / 2.0;
    cylinder_params[1] = cylinder->height;
    distance = cylinder_quadratic(cylinder_vec, cylinder_params, ray);
    return (distance);
}

float   cylinder_pt_height(t_ray ray, t_vec3 cylinder_vec[2], float distance)
{
    t_vec3  oc;
    t_vec3 tmp;
    float   m;

    oc = vec3_substract(ray.origin, cylinder_vec[0]);
    tmp = vec3_scalar_mult(cylinder_vec[1], distance);
    m = vec3_dot_product(ray.direction, tmp);
    m += vec3_dot_product(oc, cylinder_vec[1]);
    return (m);
}

t_vec3  cylinder_normal_vec(t_ray ray, t_cylinder* cylinder, float distance)
{
    float   m;
    t_vec3  res[2];
    t_vec3  intersected_pt;
    t_vec3  cylinder_vec[2];
    float   cylinder_params[2];

    cylinder_vec[0] = cylinder->center;
    cylinder_vec[1] = cylinder->orientation;
    cylinder_params[0] = cylinder->diameter / 2.0;
    cylinder_params[1] = cylinder->height;
    intersected_pt = ray_intersection_pt(ray, distance);
    m = cylinder_pt_height(ray, cylinder_vec, distance);
    res[0] = vec3_add(cylinder_vec[0], vec3_scalar_mult(cylinder_vec[1], m));
    res[1] = vec3_normalize(vec3_substract(intersected_pt, res[0]));
    return (res[1]);
}
