/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:32:26 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/07 08:44:45 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H

#define VECTOR_H

typedef struct s_vec3
{
    float   x;
    float   y;
    float   z;
}   t_vec3;

t_vec3  *vec3_allocate(float x, float y, float z);
t_vec3  vec3_create(float x, float y, float z);
float   vec3_get_dot_product(t_vec3 u, t_vec3 v);
float   vec3_get_norm(t_vec3 vector);
t_vec3  vec3_normalize(t_vec3 vector);
t_vec3  vec3_add(t_vec3 u, t_vec3 v);
t_vec3  vec3_substract(t_vec3 u, t_vec3 v);
t_vec3  vec3_multiply(t_vec3 u, t_vec3 v);
t_vec3  vec3_const_multiply(t_vec3 u, float k);
t_vec3  vec3_divide(t_vec3 u, t_vec3 v);
t_vec3 vec3_cross_product(t_vec3 u, t_vec3 v);
void    vec3_print(t_vec3 vector); // to retire

#endif