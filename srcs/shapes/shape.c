/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:44:35 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/13 12:37:43 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3  ray_intersection_pt(t_ray ray, float distance)
{
    t_vec3  intersected_pt;

    intersected_pt = vec3_scalar_mult(ray.direction, distance);
    intersected_pt = vec3_add(ray.origin, intersected_pt);
    return (intersected_pt);
}

t_vec3  ot_pt_to_lightvec(t_vec3 light_pos, t_ray ray, float distance)
{
    t_vec3  intersected_pt;

    intersected_pt = ray_intersection_pt(ray, distance);
    return (vec3_normalize(vec3_substract(light_pos, intersected_pt)));
}

t_vec3  sp_pt_to_lightvec(t_vec3 light_pos, t_ray ray, float distance)
{
    t_vec3  intersected_pt;
    t_vec3  ajusted_light;

    intersected_pt = ray_intersection_pt(ray, distance);
    ajusted_light = vec3_create(-light_pos.x, -light_pos.y, light_pos.z);
    return(vec3_normalize(vec3_substract(intersected_pt, ajusted_light)));
}

t_vec3  pt_to_lightvec(t_light  *light, t_ray ray, t_hit_pt *hit_pt)
{
    t_vec3  vector;
    t_vec3  light_pos;
    t_shape *shape;
    float   distance;

    shape = hit_pt->shape;
    distance = hit_pt->distance;
    light_pos = light->position;
    // if (shape->sphere)
    //     vector = sp_pt_to_lightvec(light_pos, ray, distance);
    // else
    vector = ot_pt_to_lightvec(light_pos, ray, distance);
    return (vector);
}

float   get_diffuse_brightness(t_vec3 lightvec, t_vec3 normal_vec)
{
    float   coef;
    float   brightness;

    coef = 0.9;
    brightness = vec3_dot_product(normal_vec, lightvec);
    brightness = fmax(brightness, 0.1);
    return (brightness * coef);
}

float   get_shiness(t_vec3 lightvec, t_vec3 normal_vec, t_ray ray, int type)
{
    float   coef;
    float   shiness;
    float   shiness_coef;
    t_vec3  halfway_vec;

    coef = 0.5;
    shiness_coef = 128.0;
    // if (type == 7)
    //     halfway_vec = vec3_add(lightvec, ray.direction);
    // else
    halfway_vec = vec3_add(lightvec, vec3_scalar_mult(ray.direction, -1));
    halfway_vec = vec3_normalize(halfway_vec);
    shiness = vec3_dot_product(normal_vec, halfway_vec);
    shiness = fmax(shiness, 0.1);
    shiness = powf(shiness, shiness_coef);
    return (shiness * coef);
}

int get_colorss(t_hit_pt* hit_pt)
{
    int     color;
    t_shape *shape;

    color = 0;
    shape = hit_pt->shape;
    if (!shape)
        return (0);
    if (shape->plane)
        color = shape->plane->color;
    else if (shape->sphere)
        color = shape->sphere->color;
    else if (shape->cylinder)
        color = shape->cylinder->color;
    return (color);
}

int get_shade_lighting(t_data *data, t_ray ray, t_hit_pt *hit_pt)
{
    t_vec3  lightvec;
    float   shade_coef;
    float   bright_coef;
    int     obj_type;

    shade_coef = 0;
    lightvec = pt_to_lightvec(data->light, ray, hit_pt);
    obj_type = hit_pt->type;
    bright_coef = get_diffuse_brightness(lightvec, hit_pt->normal_vec);
    shade_coef = get_shiness(lightvec, hit_pt->normal_vec, ray, obj_type);
    // shade_coef = 0;
    //to correct to use t_color
    int color = get_colorss(hit_pt);
    int *trgb = get_trgb_from_color(color);
    trgb[0] = 1;
    trgb[1] = fmin(255 * shade_coef + trgb[1] * bright_coef, 255);
    trgb[2] = fmin(255 * shade_coef + trgb[2] * bright_coef, 255);
    trgb[3] = fmin(255 * shade_coef + trgb[3] * bright_coef, 255);
    color = get_color_from_trgb(1, trgb[1], trgb[2], trgb[3]);
    free(trgb);
    return (color);
}
