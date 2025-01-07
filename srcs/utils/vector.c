/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:31:54 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/07 08:44:27 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3  *vec3_allocate(float x, float y, float z)
{
    t_vec3  *vector;

    vector = malloc(sizeof(t_vec3));
    if (!vector)
        return (NULL);
    vector->x = x;
    vector->y = y;
    vector->z = z;
    return (vector);
}

float   vec3_get_dot_product(t_vec3 u, t_vec3 v)
{
    return (u.x * v.x + u.y * v.y + u.z * v.z);
}

float   vec3_get_norm(t_vec3 vector)
{
    return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

t_vec3  vec3_create(float x, float y, float z)
{
    t_vec3  vector;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    return (vector);
}

t_vec3  vec3_add(t_vec3 u, t_vec3 v)
{
    return (vec3_create(u.x + v.x, u.y + v.y, u.z + v.z));
}

t_vec3  vec3_substract(t_vec3 u, t_vec3 v)
{
    return (vec3_create(u.x - v.x, u.y - v.y, u.z - v.z));
}

t_vec3  vec3_multiply(t_vec3 u, t_vec3 v)
{
    return (vec3_create(u.x * v.x, u.y * v.y, u.z * v.z));
}

t_vec3  vec3_const_multiply(t_vec3 u, float k)
{
    return (vec3_create(u.x * k, u.y * k, u.z * k));
}

t_vec3  vec3_divide(t_vec3 u, t_vec3 v)
{
    float   x;
    float   y;
    float   z;

    x = 0;
    y = 0;
    z = 0;
    if (v.x != 0)
        x = u.x / v.x;
    if (v.y != 0)
        y = u.y / v.y;
    if (v.z != 0)
        z = u.z / v.z;
    return (vec3_create(x, y, z));
}

t_vec3  vec3_normalize(t_vec3 vector)
{
    float   vector_norm;

    vector_norm = vec3_get_norm(vector);
    return (vec3_const_multiply(vector, 1.0f / vector_norm));
}

t_vec3 vec3_cross_product(t_vec3 u, t_vec3 v)
{
    t_vec3 vector;

    vector.x = u.y * v.z - u.z * v.y;
    vector.y = u.z * v.x - u.x * v.z;
    vector.z = u.x * v.y - u.y * v.x;

    return vector;
}

void    vec3_print(t_vec3 vector)
{
    printf("(x = %f, y = %f, z = %f)\n", vector.x, vector.y, vector.z);
}
