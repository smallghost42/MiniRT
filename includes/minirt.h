/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:48:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/07 10:59:34 by trazanad         ###   ########.fr       */
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

# include "../libft/libft.h"

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
void	ft_mlx_pixel_put(t_scene *scene, float x, float y, int color);
void	hook_loop(t_scene scene);

//color
int		trgb_to_color(int t, int r, int g, int b);
int		*color_to_trgb(int color);

#endif