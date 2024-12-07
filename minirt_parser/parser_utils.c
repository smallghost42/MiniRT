/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:57:36 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:23:54 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int check_file_extention(char *filename)
{
	char *str;

	if (ft_strlen(filename) < 4)
		return (0);
	str = ft_substr(filename, ft_strlen(filename) - 3, 3);
	if (strcmp(str, ".rt"))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

void free_split(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int check_first_and_count_param(char *str, t_count *count)
{
	char **str2;
	int i;

	i = 0;
	str2 = ft_split(str, ' ');
	while (str2[i])
		i++;
	if (!strcmp(str2[0], "A") && i == 3 && !valid_range_ambient(str2))
		count->a_l += 1;
	else if (!strcmp(str2[0], "C") && i == 4 && valid_range())
		count->cam += 1;
	else if (!strcmp(str2[0], "L") && i == 4 && valid_range())
		count->light += 1;
	else if (!strcmp(str2[0], "sp") && i == 4 && valid_range())
		count->sp += 1;
	else if (!strcmp(str2[0], "pl") && i == 4 && valid_range())
		count->pl += 1;
	else if (!strcmp(str2[0], "cy") && i == 6 && valid_range())
		count->cy += 1;
	else
	{
		free_split(str2);
		return (1);
	}
	free_split(str2);
	return (0);
}
