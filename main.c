/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:43:42 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/03 10:51:51 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "minilibx-linux/mlx.h"

int main(int argc, char *argv[])
{
	t_data data;

	if (argc != 2 || file_parser(argv[1]) == 1)
	{
		write(2, "\033[031merror: i will not allow it !-_-!\033[0m\n", 33);
		return (1);
	}

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
								  &data.line_length, &data.endian);

	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);

	mlx_string_put(data.mlx, data.mlx_win, 10, 10, 0x92ef60, "success");

	mlx_loop(data.mlx);
	return (0);
}
