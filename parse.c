/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:32:41 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/13 15:03:03 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_pos(t_data *data, char *path)
{
	char	cur[10000];
	char	c;
	int		fd;
	int		i;
	int		j;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (free_all(data));
	i = 0;
	j = 0;
	while (read(fd, &c, 1))
	{
		cur[i] = c;
		if (c == '\n')
		{
			cur[i] = '\0';
			if (!parse_line(data, cur, j++))
				return (free_all(data));
			i = -1;
		}
		i++;
	}
	close(fd);
	return (1);
}

int	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (data->pos && ++i < data->n)
		free(data->pos[i]);
	while (data->s_pos && ++i < data->n)
		free(data->s_pos[i]);
	free(data->pos);
	free(data->s_pos);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int	alloc(t_data *data)
{
	int	i;

	data->pos = malloc(sizeof(t_pos *) * data->n);
	data->s_pos = malloc(sizeof(t_pos *) * data->n);
	if (!data->pos || !data->s_pos)
		return (free_all(data));
	i = -1;
	while (++i < data->n)
	{
		data->pos[i] = malloc(sizeof(t_pos) * data->m);
		data->s_pos[i] = malloc(sizeof(t_pos) * data->m);
		if (!data->pos[i] || !data->s_pos[i])
			return (free_all(data));
	}
	return (1);
}

void	center_pos(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->n)
	{
		j = -1;
		while (++j < data->m)
		{
			data->pos[i][j].x -= data->m / 2;
			data->pos[i][j].y -= data->n / 2;
		}
	}
}

int	parse_map(t_data *data, char *path)
{
	init_data(data);
	if (!get_dimension(data, path) || !alloc(data))
		return (0);
	set_zero(data);
	get_pos(data, path);
	center_pos(data);
	return (1);
}
