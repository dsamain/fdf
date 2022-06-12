/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:54:24 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/22 18:11:29 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	if (!parse_map(&data, av[1]) || !data.n || !data.m)
		return (free_all(&data));
	set_scale(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "fdf");
	data.img = NULL;
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pix,
			&data.line_length, &data.endian);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	return (1);
}
