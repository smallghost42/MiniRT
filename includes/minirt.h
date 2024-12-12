/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:48:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/12 14:25:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H

# define INCLUDE_H

# define WIN_WIDTH 1920

# define WIN_HEIGHT 1080

# define PI 3.14162

# define COLOR 10523517

# include <mlx.h>

# include <stdlib.h>

#include <stdio.h>

# include <unistd.h>

# include <math.h>

# include <fcntl.h>

# include "../lib/libft/libft.h"

# include "vector.h"

# include "ray.h"

typedef struct s_scene
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		*offset;
	int		bpp;
	int		line_length;
	int		endian;
	//t_data	*data;
}	t_scene;


//mlx
void	my_mlx_pixel_put(t_scene *scene, float x, float y, int color);
void	run_hook_cycle(t_scene scene);

//color
int		get_trgb_from_color(int t, int r, int g, int b);
int		*get_color_from_trgb(int color);

//components
int		draw_sphere(int x, int y, int radius, t_scene *scene);
int		draw_plane(int x, int y, t_scene *scene);

#endif