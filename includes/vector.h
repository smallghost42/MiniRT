/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:32:26 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/09 10:31:51 by trazanad         ###   ########.fr       */
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

t_vec3  *vec3_create(float x, float y, float z);
float   vec3_dot_product(t_vec3 u, t_vec3 v);
float   vec3_norm(t_vec3 vector);
t_vec3  *vec3_addition(t_vec3 u, t_vec3 v);
t_vec3  *vec3_substraction(t_vec3 u, t_vec3 v);
t_vec3  *vec3_multiply(t_vec3 u, t_vec3 v);
t_vec3  *vec3_const_multiply(t_vec3 u, float k);
t_vec3  *vec3_division(t_vec3 u, t_vec3 v);

#endif