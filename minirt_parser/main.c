/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:43:42 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/17 08:12:19 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc != 2 || file_parser(argv[1], data) == 1)
	{
		global_free(data);
		free(data);
		return (1);
	}
	global_free(data);
	free(data);
	printf("\033[32mparse success\n\033[0m");
	return (0);
}
