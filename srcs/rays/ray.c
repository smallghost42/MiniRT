/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:31:05 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 13:53:09 by trazanad         ###   ########.fr       */
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


