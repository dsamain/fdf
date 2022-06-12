/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:11:40 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/22 18:18:46 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	k_hook(int keycode, void *void_data)
{
	if (keycode == 53)
	{
		free_all((t_data *)void_data);
		exit(0);
	}
	return (0);
}

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
	mlx_key_hook(data.win, k_hook, &data);
	mlx_loop(data.mlx);
	return (1);
}
