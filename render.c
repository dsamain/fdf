/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:55:33 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/13 15:06:42 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	get_color(t_data *data, int factor)
{
	return ((ft_min(data->max_r, factor * data->r + data->offset
				* data->r) << 16)
		+ (ft_min(data->max_g, factor * data->g + data->offset * data->g) << 8)
		+ ft_min(data->max_b, factor * data->b + data->offset * data->b));
}

void	draw_color_line(t_pos *p1, t_pos *p2, t_data *data, t_color *color)
{
	t_line			line;
	int				e2;
	unsigned int	col;

	col = get_color(data, ft_max(color->cs, color->ce));
	setup_line(p1, p2, &line);
	while (1)
	{
		my_mlx_pixel_put(data, line.x0, line.y0, col);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = line.err;
		if (e2 > -line.dx)
		{
			line.err -= line.dy;
			line.x0 += line.sx;
		}
		if (e2 < line.dy)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}

int	render_frame(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	update_pos(data);
	draw_image(data);
	return (1);
}

void	init_data(t_data *data)
{
	data->n = 0;
	data->m = 0;
	data->scale = 42;
	data->z_scale = data->scale / 2;
	data->incr_a = 0;
	data->incr_b = 0;
	data->r = 1;
	data->b = 2;
	data->g = 0;
	data->max_r = 255;
	data->max_g = 0;
	data->max_b = 100;
}
