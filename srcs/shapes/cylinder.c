/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:56:40 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/27 16:58:42 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	p is hit point
	C is cylinder center
	V is normalized cylinder axis unit vector
	m is distance ||C - A|| such as (P - A).V = 0
	D is the ray direction
	t is the distance
	O is the camera position
	r is the rayon
	X = O - C
*/

// t_vec3 get_sphere_normal()
// {
// 	t_vec3	normal_vec;

// 	//normal = vec3_normalize(P - C - V * m);
// 	return (normal_vec);
// }

/*
	* To calculate distance, we have
		- a = D.D - (D.V)^2
		- c = X.X - (X.V)^2 - r^2
		- b = 2 * (D.X - (D.V) * (X.V))
	and we have then,
		x = (-b -/+ sqrt(delta)) / 2a  and delta = b^2 - 4ac;
	
	and for finite cylinder we have to calculate the height
		m = D.V*t + X.V  and check m is in 0, height
*/

float	get_cylinder_point_distance(t_ray ray, t_vec3 center, t_vec3 axis_vec, float diameter, float height)
{
	float	distance;
	float	discriminant;
	float	a, b, c, x1, x2, m;
	float	radius;
	t_vec3	x;

	radius = diameter / 2.0;
	x = vec3_substract(ray.origin, center);
	a = vec3_get_dot_product(ray.direction, ray.direction) - powf(vec3_get_dot_product(ray.direction, axis_vec), 2.0);
	c = vec3_get_dot_product(x,x) - powf(vec3_get_dot_product(x, axis_vec), 2.0) - powf(radius, 2.0);
	b = 2 * (vec3_get_dot_product(ray.direction, x) - (vec3_get_dot_product(ray.direction, axis_vec) * vec3_get_dot_product(x, axis_vec)));
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	discriminant = sqrt(discriminant);
	x1 = (-b - discriminant) / ( 2 * a);
	x2 = (-b + discriminant) / ( 2 * a);
	distance = fmax(x1, x2);
	if (distance < 0)
		return (-1);
	m = vec3_get_dot_product(ray.direction, vec3_const_multiply(axis_vec, distance)) + vec3_get_dot_product(x, axis_vec);
	if (m >= 0 && m <= height)
		return (distance);
	return (-1);
}
float	get_point_heigh(t_ray ray, t_vec3 axis_vec, t_vec3 cylinder_center, float distance)
{
	t_vec3	x;
	float	m;

	x = vec3_substract(ray.origin, cylinder_center);
	m = vec3_get_dot_product(ray.direction, vec3_const_multiply(axis_vec, distance)) + vec3_get_dot_product(x, axis_vec);
	return (m);
}

//N = nrm( P-C-V*m )
t_vec3 get_cylinder_normal(t_ray ray, float distance, t_vec3 cylinder_center, t_vec3 axis_vec)
{
    t_vec3 hit_point;
    t_vec3 normal_vec, tmp;
	float	m;

	hit_point = get_sphere_hit_point(ray, distance);
    m = get_point_heigh(ray, axis_vec, cylinder_center, distance);
	tmp = vec3_add(cylinder_center, vec3_const_multiply(axis_vec, m));
	normal_vec = vec3_normalize(vec3_substract(hit_point, tmp));
    return (normal_vec);
}

static int get_diffuse_light_color(t_ray ray, float distance, t_vec3 cylinder_center, t_vec3 axis_vec)
{
    t_vec3  normal_vec;
    float   brightness;
    int     color;
    int     trgb[4];

    normal_vec = get_cylinder_normal(ray, distance, cylinder_center, axis_vec);
	//calculate hit point to light vec
    t_vec3 light_pos = vec3_create(-100, 0, 20);
	t_vec3 point_to_light_vec = get_point_to_light_vector(light_pos, ray, distance);
    brightness = fmax(vec3_get_dot_product(normal_vec, point_to_light_vec), 0.1);
    trgb[0] = 1;
    trgb[1] = roundf(255 * brightness);
    trgb[2] = roundf(5 * brightness);
    trgb[3] = roundf(10 * brightness);
    color = get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
    return (color);
}

static int get_specular_light_color(t_ray ray, float distance, t_vec3 cylinder_center, t_vec3 axis_vec) 
{
    t_vec3 normal_vec;
    t_vec3 point_to_light_vec;
    t_vec3 halfway_vec;
    float spec_brightness;
    float tmp;
    int color;
    int trgb[4];
    float shininess = 128.0;

    normal_vec = get_cylinder_normal(ray, distance, cylinder_center, axis_vec);
    t_vec3 light_pos = vec3_create(-100, 0, 20);
    point_to_light_vec = get_point_to_light_vector(light_pos, ray, distance);

    halfway_vec = vec3_normalize(vec3_add(point_to_light_vec, ray.direction));

    tmp = vec3_get_dot_product(normal_vec, halfway_vec);
    spec_brightness = powf(fmax(tmp, 0.1), shininess);

    //suppose light reflexision is white nigga
    int surface_trgb[4] = {1, 255, 255, 255};
    trgb[0] = 1;
    trgb[1] = fmin(roundf(surface_trgb[1] * spec_brightness), 255);
    trgb[2] = fmin(roundf(surface_trgb[2] * spec_brightness), 255);
    trgb[3] = fmin(roundf(surface_trgb[3] * spec_brightness), 255);

    color = get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
    return (color);
}

static int add_colors(int diffuse_color, int specular_color) 
{
    int trgb[4];
    int *diffuse_trgb;
    int *specular_trgb;
    
	diffuse_trgb = get_trgb_from_color(diffuse_color);
	specular_trgb = get_trgb_from_color(specular_color);

    trgb[0] = 1;
    trgb[1] = fmin(diffuse_trgb[1] * 0.8 + specular_trgb[1] * 0.5, 255);
    trgb[2] = fmin(diffuse_trgb[2] * 0.8 + specular_trgb[2] * 0.5, 255);
    trgb[3] = fmin(diffuse_trgb[3] * 0.8 + specular_trgb[3] * 0.5, 255); 
    free(diffuse_trgb);
    free(specular_trgb);
    return get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
}

int render_cylinder(t_scene *scene, t_vec3 camera_pos, t_vec3 cylinder_center, t_vec3 axis_vec, float diameter, float height)
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
            image_plane_coord[0] = get_x_image_plane(coord[0], fov_angle);
            image_plane_coord[1] = get_y_image_plane(coord[1], fov_angle);

            ray.direction = get_ray_direction(image_plane_coord);
            ray.origin = camera_pos;

			current_distance = get_cylinder_point_distance(ray, cylinder_center, axis_vec, diameter, height);
            if (current_distance >= 0)
            {
                if (distance > current_distance)
                    distance = current_distance;
				// int color = get_color_from_trgb(1, 255, 0, 0);
				int	color = add_colors(get_diffuse_light_color(ray, current_distance, cylinder_center, axis_vec), 
                           get_specular_light_color(ray, current_distance, cylinder_center, axis_vec));

				// int color = get_diffuse_light_color(ray, current_distance, cylinder_center, axis_vec);
				// int color = get_specular_light_color(ray, current_distance, cylinder_center, axis_vec);
                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
