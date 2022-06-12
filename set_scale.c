/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:50:34 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/13 15:06:54 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_size(t_data *data)
{
	int	mn;
	int	mx;
	int	i;
	int	j;

	mn = 2147483647;
	mx = -2147483648;
	i = -1;
	while (++i < data->n)
	{
		j = -1;
		while (++j < data->m)
		{
			mn = ft_min(mn, data->pos[i][j].z);
			mx = ft_max(mx, data->pos[i][j].z);
		}
	}
	data->mn_z = mn;
	data->mx_z = mx;
	return (ft_max((mx) * data->z_scale * 1.5,
			ft_max(data->n, data->m) * data->scale * 1.2));
}

void	adjust_z(t_data *data)
{
	int	i;
	int	j;

	data->mx_z += -data->mn_z + 1;
	i = -1;
	while (++i < data->n)
	{
		j = -1;
		while (++j < data->m)
		{
			data->pos[i][j].z += -data->mn_z + 1;
		}
	}
	data->mn_z = 0;
}

void	set_scale(t_data *data)
{
	int	size;

	size = get_size(data);
	adjust_z(data);
	if (size < 1080)
	{
		data->height = size * 1.2f;
		data->width = size * 1.6f;
	}
	else
	{
		data->height = 1080;
		data->width = 1920;
		data->scale /= (double)size / 1080;
		data->z_scale /= (double)size / 1080;
	}
	data->x_gap = data->width / 2;
	data->y_gap = data->height / 2;
	data->offset = 2;
	data->mn_z = -10;
	data->ratio = (double)(256 / (double)ft_abs(data->mx_z - data->mn_z));
}
