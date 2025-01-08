/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:48:54 by trazanad          #+#    #+#             */
/*   Updated: 2025/01/08 10:47:43 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H

# define INCLUDE_H

# define WIN_WIDTH 1366

# define WIN_HEIGHT 768

# define PI 3.14162

# define COLOR 10523517

# define EPSILON 0.000001

# include "clib.h"

# include "vector.h"

# include "ray.h"

# include "utils.h"

# include "parser.h"

#include "test.h" //////////////////////to delete

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
	t_data	*data;
}	t_scene;

int render_scene(t_scene *scene);

#endif