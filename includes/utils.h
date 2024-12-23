/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:00:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 14:06:27 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

#include "minirt.h"

//mlx
void	my_mlx_pixel_put(t_scene *scene, float x, float y, int color);
void	run_hook_cycle(t_scene scene);

//color
int		get_trgb_from_color(int t, int r, int g, int b);
int		*get_color_from_trgb(int color);

//image plane
float   get_aspect_ratio(void);
float   get_x_image_plane(int x, int fov);
float   get_y_image_plane(int y, int fov);

#endif