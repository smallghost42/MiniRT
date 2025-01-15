/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:48:01 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/15 12:08:08 by trazanad         ###   ########.fr       */
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
t_vec3  get_ray_direction(float coord[2]);
t_vec3  get_point_to_light_vector(t_vec3 light_pos, t_ray ray, float distance);
t_vec3	get_sphere_hit_point(t_ray ray, float distance);
t_vec3 get_point_to_light_vector0(t_vec3 light_pos, t_ray ray, float distance);

//sphere
float     get_sphere_pt_distance(t_ray ray, t_vec3 center, float radius);
int     render_sphere(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius);

//plane
int render_plane(t_scene *scene, t_vec3 camera_pos, t_vec3 plane_point, t_vec3 plane_normal);
float	get_plane_pt_distance(t_ray ray, t_vec3 plane_point, t_vec3 plane_normal);
//cylinder
int render_cylinder(t_scene *scene, t_vec3 camera_pos, t_vec3 cylinder_center, t_vec3 axis_vec, float diameter, float height);
float	get_cylinder_pt_distance(t_ray ray, t_vec3 center, t_vec3 axis_vec, float diameter, float height);

#endif
