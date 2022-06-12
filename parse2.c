/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:57:39 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/22 20:02:47 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_line(t_data *data, char *cur, int idx)
{
	char	*s;
	int		i;	
	int		j;
	int		ws;

	j = 0;
	i = -1;
	while (cur[++i])
	{
		ws = 0;
		while (cur[i + ws] && cur[i + ws] != ' ')
			ws++;
		if (ws)
		{
			s = ft_substr(cur, i, ws);
			if (!s)
				return (0);
			data->pos[idx][j++].z = ft_atoi(s);
			free(s);
		}
		i += ws;
	}
	return (1);
}

int	count_word(char *s)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] && s[i] != ' ')
		{
			cnt++;
			while (s[i] && s[i] != ' ')
				i++;
		}
	}
	return (cnt);
}

int	get_dimension(t_data *data, char *path)
{
	char	cur[100000];
	int		fd;
	int		i;
	char	c;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (free_all(data));
	i = -1;
	while (read(fd, &c, 1) && ++i > -1)
	{
		cur[i] = c;
		if (c == '\n')
			cur[i] = 0;
		if (!cur[i])
			break ;
	}
	data->m = count_word(cur);
	close(fd);
	fd = open(path, O_RDONLY);
	while (read(fd, &c, 1))
		data->n += c == '\n';
	close(fd);
	return (1);
}

void	set_zero(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->n)
	{
		j = -1;
		while (++j < data->m)
		{
			data->pos[i][j].x = j;
			data->pos[i][j].y = i;
			data->pos[i][j].z = 0;
		}
	}
}
