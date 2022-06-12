/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:46:23 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/13 14:57:27 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_trgb(int t, int r, int g, int b)
{
	return ((t << 24) + (r << 16) + (g << 8) + b);
}
