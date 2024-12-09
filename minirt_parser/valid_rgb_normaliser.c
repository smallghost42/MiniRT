/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb_normaliser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:46:25 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:46:33 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int check_valid_rgb(char *color)
{
  char **rgb;
  int i;

  i = 0;
  rgb = ft_split(color, ',');
  if (!rgb || strcmp(rgb[0], color) == 0)
	return (1);
  while (rgb[i])
  {
	if (ft_valid_int(rgb[i]) || ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
	{
	  free_split(rgb);
	  return (1);
	}
	i++;
  }
  if (i != 3)
	return (1);
  return (0);
}
