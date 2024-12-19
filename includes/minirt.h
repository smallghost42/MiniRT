/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:48:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/18 10:10:15 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H

# define INCLUDE_H

# define WIN_WIDTH 1920

# define WIN_HEIGHT 1020

# define PI 3.14162

# define COLOR 10523517

# include <mlx.h>

# include <stdlib.h>

#include <stdio.h>

# include <unistd.h>

# include <math.h>

# include <fcntl.h>

# include <X11/keysym.h>

# include <X11/keysymdef.h>

# include "../lib/libft/libft.h"

# include "vector.h"

# include "ray.h"

# include "utils.h"

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

//components
int		draw_sphere(int x, int y, int radius, t_scene *scene);
int		draw_plane(int x, int y, t_scene *scene);

#endif