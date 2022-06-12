/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:37:50 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/13 15:06:34 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setup_line(t_pos *p1, t_pos *p2, t_line *line)
{
	line->x0 = p1->x;
	line->y0 = p1->y;
	line->x1 = p2->x;
	line->y1 = p2->y;
	line->sx = -1;
	if (line->x0 < line->x1)
		line->sx = 1;
	line->sy = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	line->err = -line->dy;
	if (line->dx > line->dy)
		line->err = line->dx;
	line->err /= 2;
}

void	draw_line(t_pos *p1, t_pos *p2, t_data *data)
{
	t_line	line;
	int		e2;

	setup_line(p1, p2, &line);
	while (1)
	{
		my_mlx_pixel_put(data, line.x0, line.y0, 0x00FFFFFF);
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

void	set_ratio(t_data *data, t_color *color, int z0, int z1)
{
	color->cs = (double)ft_abs(data->mn_z - z0) * data->ratio;
	color->ce = (double)ft_abs(data->mn_z - z1) * data->ratio;
}

void	set_draw(t_data *data, t_color *color, int i, int j)
{
	if (j < data->m - 1)
		set_ratio(data, color,
			data->s_pos[i][j].z, data->s_pos[i][j + 1].z);
	if (j < data->m - 1)
		draw_color_line(data->s_pos[i] + j,
			data->s_pos[i] + j + 1, data, color);
	if (i < data->n - 1)
		set_ratio(data, color,
			data->s_pos[i][j].z, data->s_pos[i + 1][j].z);
	if (i < data->n - 1)
		draw_color_line(data->s_pos[i] + j,
			data->s_pos[i + 1] + j, data, color);
}

void	draw_image(t_data *data)
{
	t_color	color;
	int		i;
	int		j;

	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pix,
			&data->line_length, &data->endian);
	i = -1;
	while (++i < data->n)
	{
		j = -1;
		while (++j < data->m)
		{
			set_draw(data, &color, i, j);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
