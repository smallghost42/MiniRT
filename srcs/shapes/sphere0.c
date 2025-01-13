/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:46:11 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/13 11:14:31 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//note only sphere is need the one without 0 dude

float get_sphere_pt_distance(t_ray ray, t_vec3 center, float radius)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;
    float   distance;
    float   discriminant;
    
    // oc = vec3_substract(center, ray.origin);
	oc = vec3_substract(ray.origin, center);
    a = vec3_dot_product(ray.direction, ray.direction);
    b = 2 * vec3_dot_product(oc, ray.direction);
    c = vec3_dot_product(oc, oc) - radius * radius;
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

    hit_point = vec3_add(ray.origin, vec3_scalar_mult(ray.direction, distance));
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

// t_vec3 get_point_to_light_vector(t_vec3 light_pos, t_ray ray, float distance) {
//     t_vec3 hit_point;

//     hit_point = get_sphere_hit_point(ray, distance);
//     return (vec3_normalize(vec3_substract(light_pos, hit_point)));
// }

t_vec3  get_point_to_light_vector(t_vec3 light_pos, t_ray ray, float distance)
{
	t_vec3	point_to_light;
	t_vec3	hit_point;
	t_vec3	ajusted_light_pos;

	hit_point = get_sphere_hit_point(ray, distance);
	// ajusted_light_pos = vec3_create(-light_pos.x, -light_pos.y, light_pos.z);
	ajusted_light_pos = vec3_create(light_pos.x, light_pos.y, light_pos.z);
	point_to_light = vec3_substract(hit_point, ajusted_light_pos);
	return (vec3_normalize(point_to_light));
}

static int get_diffuse_light_color(t_ray ray, float distance, t_vec3 sphere_center)
{
    t_vec3  normal_vec;
    float   brightness;
    int     color;
    int     trgb[4];

    normal_vec = get_sphere_normal(ray, distance, sphere_center);
	//calculate hit point to light vec
    t_vec3 light_pos = vec3_create(40, 0, 70);
	t_vec3 point_to_light_vec = get_point_to_light_vector(light_pos, ray, distance);
    brightness = fmax(vec3_dot_product(normal_vec, point_to_light_vec), 0.1);
    trgb[0] = 1;
    trgb[1] = roundf(255 * brightness);
    trgb[2] = roundf(0 * brightness);
    trgb[3] = roundf(0 * brightness);
    color = get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
    return (color);
}

static int get_specular_light_color(t_ray ray, float distance, t_vec3 sphere_center) 
{
    t_vec3 normal_vec;
    t_vec3 point_to_light_vec;
    t_vec3 halfway_vec;
    float spec_brightness;
    float tmp;
    int color;
    int trgb[4];
    float shininess = 64.0;

    normal_vec = vec3_normalize(get_sphere_normal(ray, distance, sphere_center));
    t_vec3 light_pos = vec3_create( 40, 0, 70);
   point_to_light_vec = get_point_to_light_vector(light_pos, ray, distance);

    // halfway_vec = vec3_normalize(vec3_add(point_to_light_vec, vec3_scalar_mult(ray.direction, -1)));
    halfway_vec = vec3_normalize(vec3_add(point_to_light_vec, ray.direction));

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
    trgb[1] = fmin(diffuse_trgb[1] * 0.5 + specular_trgb[1] * 0.5 + 0.3 * 255, 255);
    trgb[2] = fmin(diffuse_trgb[2] * 0.5 + specular_trgb[2] * 0.5 + 0.3 * 0, 255);
    trgb[3] = fmin(diffuse_trgb[3] * 0.5 + specular_trgb[3] * 0.5 + 0.3 * 0, 255); 
    free(diffuse_trgb);
    free(specular_trgb);
    return get_color_from_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
}

//test one
int is_in_shadow(t_vec3 hit_point) 
{
    t_vec3 light_pos = vec3_create(100, 0, 0);
    t_ray  ray;
    t_vec3 sphere_center;
    float  d;
    float  radius;
    float  distance_to_light;

    sphere_center = vec3_create(0.0, 0, -20.6);    
    radius = 12.6;
    ray.origin = hit_point;
    ray.direction = vec3_normalize(vec3_substract(light_pos, hit_point)); 
    distance_to_light = vec3_norm(vec3_substract(light_pos, hit_point));
    d = get_sphere_pt_distance(ray, sphere_center, radius);
    if (d > 0 && d < distance_to_light)
        return (1);
    return (0);
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
            image_plane_coord[0] = get_x_projected(coord[0], fov_angle);
            image_plane_coord[1] = get_y_projected(coord[1], fov_angle);

            ray.direction = get_ray_direction(image_plane_coord);
            ray.origin = camera_pos;
            current_distance = get_sphere_pt_distance(ray, sphere_center, radius);
		// printf("%f\n", current_distance);
            if (current_distance >= 0)
            {
                if (distance > current_distance)
                    distance = current_distance;
                //apply diffuse light from camera
                // int color= 255;
				// int	color = add_colors(get_diffuse_light_color(ray, current_distance, sphere_center), 
                //            get_specular_light_color(ray, current_distance, sphere_center));

				// int color = get_diffuse_light_color(ray, current_distance, sphere_center);
				int color = get_specular_light_color(ray, current_distance, sphere_center);
                // if (radius != 12.6 && is_in_shadow(get_sphere_hit_point(ray, current_distance)))
                // my_mlx_pixel_put(scene, coord[0], coord[1], get_color_from_trgb(1, 20, 20, 10));
                // else
                my_mlx_pixel_put(scene, coord[0], coord[1], color);
                // my_mlx_pixel_put(scene, coord[0], coord[1], COLOR);
            }
            coord[1]++;
        }
        coord[0]++;
    }
    return (0);
}
