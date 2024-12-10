/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:48:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/09 10:32:08 by trazanad         ###   ########.fr       */
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

# include <unistd.h>

# include <math.h>

# include <fcntl.h>

# include "../lib/libft/libft.h"

# include "vector.h"

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
	// map;
}	t_scene;


//mlx
void	float_mlx_pixel_put(t_scene *scene, float x, float y, int color);
void	int_mlx_pixel_put(t_scene *scene, int x, int y, int color);
void	hook_loop(t_scene scene);

//color
int		trgb_to_color(int t, int r, int g, int b);
int		*color_to_trgb(int color);

//components
int		draw_sphere(int x, int y, int radius, t_scene *scene);
int		draw_plane(int x, int y, t_scene *scene);

#endif