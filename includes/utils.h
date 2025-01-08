/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:00:47 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/08 08:35:38 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

#include "minirt.h"

//mlx
void	my_mlx_pixel_put(t_scene *scene, float x, float y, int color);
void	run_hook_cycle(t_scene scene);
void	print_direction();

//color
int		get_color_from_trgb(int t, int r, int g, int b);
int		*get_trgb_from_color(int color);

//image plane
float   get_aspect_ratio(void);
float   get_x_projected(int x, int fov);
float   get_y_projected(int y, int fov);

#endif