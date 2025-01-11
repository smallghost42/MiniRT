/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:29:59 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/11 14:34:35 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_plane_pt_distance(t_ray ray, t_vec3 plane_point, t_vec3 plane_normal)
{
	float	distance;
	t_vec3	camera_to_point;

	camera_to_point = vec3_substract(plane_point, ray.origin);
	distance = vec3_dot_product(plane_normal, camera_to_point) / vec3_dot_product(plane_normal, ray.direction);
	return (distance);
}

static int get_diffuse_light_color(t_ray ray, float distance, t_vec3 normal_vec)
{
    float   brightness;
    int     color;
    int     trgb[4];

	//calculate hit point to light vec
    t_vec3 light_pos = vec3_create(0.0, 50.0, 0.0);
	t_vec3 point_to_light_vec = get_point_to_light_vector0(light_pos, ray, distance);
    brightness = fmax(vec3_dot_product(normal_vec, point_to_light_vec), 0.1);
    trgb[0] = 1;
    trgb[1] = roundf(0 * brightness);
    trgb[2] = roundf(10 * brightness);
    trgb[3] = roundf(255 * brightness);
    color = get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
    return (color);
}


static int get_specular_light_color(t_ray ray, float distance, t_vec3 normal_vec) 
{
    t_vec3 point_to_light_vec;
    t_vec3 halfway_vec;
    float spec_brightness;
    float tmp;
    int color;
    int trgb[4];
    float shininess = 128.0;

    t_vec3 light_pos = vec3_create(0.0, 50.0, 0.0);
    point_to_light_vec = get_point_to_light_vector0(light_pos, ray, distance);

    // halfway_vec = vec3_normalize(vec3_add(point_to_light_vec, ray.direction));
    halfway_vec = vec3_normalize(vec3_add(point_to_light_vec, vec3_scalar_mult(ray.direction, -1)));


    tmp = vec3_dot_product(normal_vec, halfway_vec);
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
    trgb[1] = fmin(diffuse_trgb[1] * 0.8 + specular_trgb[1] * 0.5 + 0.4 * 0, 255);
    trgb[2] = fmin(diffuse_trgb[2] * 0.8 + specular_trgb[2] * 0.5 + 0.4 * 10, 255);
    trgb[3] = fmin(diffuse_trgb[3] * 0.8 + specular_trgb[3] * 0.5 + 0.4 * 255, 255); 
    free(diffuse_trgb);
    free(specular_trgb);
    return get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
}


int render_plane(t_scene *scene, t_vec3 camera_pos, t_vec3 plane_point, t_vec3 plane_normal)
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
            image_plane_coord[0] = get_x_projected(coord[0], fov_angle);
            image_plane_coord[1] = get_y_projected(coord[1], fov_angle);

            ray.direction = get_ray_direction(image_plane_coord);
            ray.origin = camera_pos;

            current_distance = get_plane_pt_distance(ray, plane_point, plane_normal);
            if (current_distance >= 0)
            {
                if (distance > current_distance)
                    distance = current_distance;
				// int color = get_color_from_trgb(1, 0, 255, 255);
				int	color = add_colors(get_diffuse_light_color(ray, current_distance, plane_normal), 
                           get_specular_light_color(ray, current_distance, plane_normal));

				// int color = get_diffuse_light_color(ray, current_distance, plane_normal);
				// int color = get_specular_light_color(ray, current_distance, plane_normal);

                my_mlx_pixel_put(scene, coord[0], coord[1], color);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
