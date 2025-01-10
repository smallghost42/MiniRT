/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadowing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:13:48 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/10 13:49:19 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sphere_shadow(t_sphere* spheres, t_ray ray, float distance)
{
	float	d;
	float	radius;
	t_vec3	center;
	t_sphere*	sphere_next;

	if (spheres)
	{
		d = get_sphere_pt_distance(ray, spheres->center, spheres->diameter / 2.0);
		if (d > 0 && d < distance ) // ==0
			return (1);
		sphere_next = spheres->next;
		while (sphere_next)
		{
			center = sphere_next->center;
			radius = sphere_next->diameter / 2.0;
			d = get_sphere_pt_distance(ray, center, radius);
			if (d > 0 && d < distance ) // ==0
				return (1);
			sphere_next = sphere_next->next;
		}
	}
	return (0);
}


// int sphere_shadow(t_sphere* spheres, t_ray ray, float distance)
// {
//     float d;
//     float radius;
//     t_vec3 center;
//     t_sphere* sphere_next;

//     if (spheres)
//     {
//         // Calculate the distance to the intersection point of the ray with the sphere
//         d = get_sphere_pt_distance(ray, spheres->center, spheres->diameter / 2.0);
        
//         // Check if the intersection distance is positive and less than the distance, avoiding self-shadowing with epsilon
//         if (d > EPSILON && d < distance)
//             return (1); // Shadow found
        
//         // Iterate through the rest of the spheres
//         sphere_next = spheres->next;
//         while (sphere_next)
//         {
//             center = sphere_next->center;
//             radius = sphere_next->diameter / 2.0;
//             d = get_sphere_pt_distance(ray, center, radius);

//             // Check if the intersection distance is positive and less than the distance, avoiding self-shadowing with epsilon
//             if (d > EPSILON && d < distance)
//                 return (1); // Shadow found
            
//             sphere_next = sphere_next->next;
//         }
//     }
//     return (0); // No shadow
// }


int	obj_is_shadowed(t_data* data, t_ray ray, float distance)
{
	float		d;
	float		shadow;
	float		shape_shadow[3];
	t_shape*	shape;

	shape = data->shape;
	shape_shadow[0] = 0;
	shape_shadow[1] = 0;
	shape_shadow[2] = 0;
	shadow = shape_shadow[0];
	shadow = fmax(shadow, shape_shadow[1]);
	shadow = fmax(shadow, shape_shadow[2]);
	return (shadow);
}

int is_obj_shadowed(t_data* data, t_ray ray, t_shape** visible_object, float distance)
{
	int			is_shadowed;
	float		pt_light_distance;
	t_ray		secondary_ray;
	t_light		*light;
    t_vec3		hitted_pt;

	is_shadowed = 0;
    if (!(*visible_object))
        return (1);
	hitted_pt = get_sphere_hit_point(ray, distance);
	//for every light
	light = data->light;
	pt_light_distance = vec3_get_norm(vec3_substract(light->position, hitted_pt));
	secondary_ray.direction = hitted_pt;
	secondary_ray.direction = vec3_normalize(vec3_substract(light->position, hitted_pt));
	is_shadowed = obj_is_shadowed(data, secondary_ray, pt_light_distance);
    return (is_shadowed);
}

