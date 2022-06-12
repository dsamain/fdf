/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:42:48 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/13 15:16:57 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook2(int keycode, t_data *data)
{
	if (keycode == 24)
		data->scale++;
	else if (keycode == 27)
		data->scale--;
	else if (keycode == 92)
		data->z_scale++;
	else if (keycode == 88)
		data->z_scale--;
	else if (keycode == 3)
		data->offset++;
	else if (keycode == 53)
	{
		free_all(data);
		exit(0);
	}
}

int	key_hook(int keycode, void *void_data)
{
	t_data	*data;

	data = void_data;
	if (keycode == 124)
		data->x_gap -= 100;
	else if (keycode == 123)
		data->x_gap += 100;
	else if (keycode == 126)
		data->y_gap += 100;
	else if (keycode == 125)
		data->y_gap -= 100;
	else if (keycode == 35)
		data->incr_a += 0.01;
	else if (keycode == 31)
		data->incr_a -= 0.01;
	else if (keycode == 37)
		data->incr_b += 0.01;
	else if (keycode == 40)
		data->incr_b -= 0.01;
	else
		key_hook2(keycode, data);
	return (1);
}

int	get_mouse_pos(int x, int y, void *void_data)
{
	t_data	*data;

	data = void_data;
	data->alpha = (double)x / 42;
	data->beta = (double)y / 42;
	return (1);
}
