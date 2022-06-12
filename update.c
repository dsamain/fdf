/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:12:05 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/12 07:38:32 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_angle(t_data *data)
{
	data->alpha += data->incr_a;
	data->beta += data->incr_b;
}

double	rotate_z(t_data *data, int i, int j, double *tmp_y)
{
	*tmp_y = sin(data->alpha) * (data->pos[i][j].x)
		+ cos(data->alpha) * data->pos[i][j].y;
	return (cos(data->alpha) * data->pos[i][j].x
		- sin(data->alpha) * data->pos[i][j].y);
}

double	rotate_x(t_data *data, int i, int j, double *tmp_z)
{
	*tmp_z = sin(data->beta) * (data->pos[i][j].x)
		+ cos(data->beta) * data->pos[i][j].y;
	return (cos(data->beta) * data->pos[i][j].x
		- sin(data->beta) * data->pos[i][j].y);
}

void	update_pos(t_data *data)
{
	int		i;
	int		j;
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;
	double sin_beta;
	double cos_beta;

	sin_beta = sin(data->beta);
	cos_beta = cos(data->beta);
	update_angle(data);
	i = -1;
	while (++i < data->n)
	{
		j = -1;
		while (++j < data->m)
		{
			tmp_x = rotate_z(data, i, j, &tmp_y);
			tmp_z = sin_beta * (tmp_y) + cos_beta
				* data->pos[i][j].z * (double)data->z_scale / data->scale;
			tmp_y = cos_beta * tmp_y - sin_beta
				* data->pos[i][j].z * (double)data->z_scale / data->scale;
			data->s_pos[i][j].x = data->x_gap
				+ (tmp_x - tmp_y) * data->scale / sqrt(2);
			data->s_pos[i][j].y = data->y_gap + ((tmp_x + 2 * tmp_y)
					* data->scale - (tmp_z * data->z_scale)) / sqrt(6);
			data->s_pos[i][j].z = data->pos[i][j].z;
		}
	}
}
