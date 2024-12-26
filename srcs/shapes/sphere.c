/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:46:11 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/26 03:17:44 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float get_sphere_pt_distance(t_ray ray, t_vec3 center, float radius)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;
    float   distance;
    float   discriminant;
    
    oc = vec3_substract(center, ray.origin);
    a = vec3_get_dot_product(ray.direction, ray.direction);
    b = -2 * vec3_get_dot_product(oc, ray.direction);
    c = vec3_get_dot_product(oc, oc) - radius * radius;
    discriminant = b * b - (4 * a * c);
    if (discriminant < 0)
        return (-1);
    discriminant = sqrt(discriminant);
    distance = fmax((- b - discriminant) / (2 * a), (- b + discriminant) / (2 * a));
    return (distance);
}

static float is_pixel_visible(float coord[2], t_vec3 camera_pos, t_vec3 sphere_center, float radius)
{
    t_ray   ray;
    t_vec3  ray_direction;

    ray_direction = vec3_create(coord[0], coord[1], -1); // replace by camera orientation vec
    ray = ray_create(camera_pos, vec3_normalize(ray_direction));
    return (get_sphere_pt_distance(ray, sphere_center, radius));
}

t_vec3	get_sphere_hit_point(t_ray ray, float distance)
{
	t_vec3	hit_point;

    hit_point = vec3_add(ray.origin, vec3_const_multiply(ray.direction, distance));
	return (hit_point);
}

t_vec3 get_sphere_normal(t_ray ray, float distance, t_vec3 sphere_center)
{
    t_vec3 hit_point;
    t_vec3 normal_vec;

	hit_point = get_sphere_hit_point(ray, distance);
    // Calculate the normal vector
    normal_vec = vec3_substract(hit_point, sphere_center);
    normal_vec = vec3_normalize(normal_vec);

    return (normal_vec);
}

t_vec3  get_point_to_light_vector(t_vec3 light_pos, t_ray ray, float distance)
{
	t_vec3	point_to_light;
	t_vec3	hit_point;
	t_vec3	ajusted_light_pos;

	hit_point = get_sphere_hit_point(ray, distance);
	ajusted_light_pos = vec3_create(-light_pos.x, -light_pos.y, light_pos.z);
	point_to_light = vec3_substract(hit_point, ajusted_light_pos);
	return (vec3_normalize(point_to_light));
}

int get_diffuse_light_color(t_ray ray, float distance, t_vec3 sphere_center)
{
    t_vec3  normal_vec;
    float   brightness;
    t_vec3  camera_orientation;
    int     color;
    int     trgb[4];

    // test light came from camera dude
    camera_orientation = vec3_create(0, 0, -1);
    normal_vec = get_sphere_normal(ray, distance, sphere_center);
	//calculate hit point to light vec
	t_vec3 light_pos = vec3_create(0, -100, 0);
	t_vec3 point_to_light_vec = get_point_to_light_vector(light_pos, ray, distance);
    brightness = fmax(vec3_get_dot_product(normal_vec, point_to_light_vec), 0.1);
    trgb[0] = 1;
    trgb[1] = roundf(10 * brightness);
    trgb[2] = roundf(255 * brightness);
    trgb[3] = roundf(255 * brightness);
    color = get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
    return (color);
}

int render_sphere(t_scene *scene, t_vec3 camera_pos, t_vec3 sphere_center, float radius)
{
    int     coord[2]; //x, y
    float   image_plane_coord[2];
    float   fov_angle;
    float   current_distance;
    float   distance;
    t_ray   ray;
    t_vec3  normal_vec;

    coord[0] = 0;
    fov_angle = 70.0;
    distance = INFINITY;

    while (coord[0] < WIN_WIDTH)
    {
        coord[1] = 0;
        while (coord[1] < WIN_HEIGHT)
        {
            // Map pixel to image plane
            image_plane_coord[0] = get_x_image_plane(coord[0], fov_angle);
            image_plane_coord[1] = get_y_image_plane(coord[1], fov_angle);

            ray.direction = get_ray_direction(image_plane_coord);
            ray.origin = camera_pos;

            current_distance = get_sphere_pt_distance(ray, sphere_center, radius);
            if (current_distance >= 0)
            {
                if (distance > current_distance)
                    distance = current_distance;
                //apply diffuse light from camera
                int color = get_diffuse_light_color(ray, current_distance, sphere_center);
                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
