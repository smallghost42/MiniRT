/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:48:01 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 14:28:48 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H

#define RAY_H

#include "vector.h"

typedef struct s_scene t_scene;

typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  direction;
}   t_ray;

t_ray   *ray_allocate(t_vec3 origin, t_vec3 direction);
t_ray   ray_create(t_vec3 origin, t_vec3 direction);
t_vec3  get_intersection(t_ray ray, float ray_param);
int     get_sphere_pt_distance(t_ray ray, t_vec3 center, float radius);
int     render_sphere(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius);

#endif
