/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadowing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:13:48 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/14 14:39:14 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int sphere_shadow(t_sphere* spheres, t_ray ray, float distance, t_shape* shape)
{
    float d;
    float radius;
    t_vec3 center;
    t_sphere* sphere_next;

    while (spheres)
    {
		if (shape->sphere != NULL && shape->sphere == spheres)
        	spheres = spheres->next;
		if (spheres == NULL)
			break;
        center = spheres->center;
        radius = spheres->diameter / 2.0;
        d = sphere_ray_hit_distance(ray, center, radius);
        if (d > EPSILON && d < distance)
            return (1);
        spheres = spheres->next;
    }
    return (0);
}

int cylinder_shadow(t_cylinder* cylinders, t_ray ray, float distance, t_shape* shape)
{
    float d;
    t_cylinder* cylinder_next;

    while (cylinders)
    {
		if (shape->cylinder != NULL && shape->cylinder == cylinders)
        	cylinders = cylinders->next;
		if (cylinders == NULL)
			break;
        d = cylinder_ray_hit_distance(ray, cylinders);
        if (d > EPSILON && d < distance)
        {
            return (1);
        }
        cylinders = cylinders->next;
    }
    return (0);
}

int	obj_is_shadowed(t_data* data, t_ray ray, float distance, t_shape *s)
{
	float		d;
	int		shadow;
	int		shape_shadow[3];
	t_shape*	shape;

	shape = data->shape;
	shape_shadow[0] = 0;
	shape_shadow[1] = sphere_shadow(shape->sphere, ray, distance, s);
	shape_shadow[2] = cylinder_shadow(shape->cylinder, ray, distance, s);
	shadow = shape_shadow[1];
    if (shadow < shape_shadow[2])
        shadow = shape_shadow[2];
	// shadow = fmax(shadow, shape_shadow[1]);
	// shadow = fmax(shadow, shape_shadow[2]);
    // shadow = 0;
	return (shadow);
}

int is_obj_shadowed(t_data* data, t_ray ray, t_hit_pt** hit_pt)
{
    int is_shadowed = 0;
    t_vec3 lightvec;
    t_ray ray_2;
    t_light* light;

    light = data->light;
    lightvec = vec3_substract(light->position, (*hit_pt)->pt);
    ray_2.origin = (*hit_pt)->pt;
    ray_2.direction = vec3_substract(light->position, (*hit_pt)->pt);
    if (obj_is_shadowed(data, ray_2, vec3_norm(lightvec), (*hit_pt)->shape))
        return (1);
    return (0);
}
