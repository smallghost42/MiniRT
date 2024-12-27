/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:40:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/27 08:08:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H

# define TEST_H

#include "minirt.h"

int	mute_arg(int argc, char **argv);
int	draw_some_sphere(t_scene *scene);

//
int	draw_some_plane(t_scene *scene);

//
int	draw_some_cylinder(t_scene *scene);

#endif