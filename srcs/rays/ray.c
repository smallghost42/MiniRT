/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:31:05 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/10 10:38:34 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
    - No transformation is yet applied to these calcul (no FOV transformation, projection, center translation)
*/

t_vec3  *get_intersection_point(t_vec3 origin, t_vec3 direction, float ray_param)
{
    t_vec3  *vector;
    t_vec3  *tmp;

    tmp = vec3_const_multiply(direction, ray_param);
    vector = vec3_addition(origin, *tmp);
    free(tmp);
    return (vector);
}
