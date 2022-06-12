/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:00:05 by dsamain           #+#    #+#             */
/*   Updated: 2021/11/22 17:46:48 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include <stdio.h>

typedef struct s_pos {
	int	x;
	int	y;
	int	z;
}	t_pos;

typedef struct s_line {
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef struct s_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pix;
	int				line_length;
	int				endian;
	int				scale;
	int				z_scale;
	int				width;
	int				height;
	int				center_x;
	int				center_y;
	int				x_gap;
	int				y_gap;
	unsigned int	color;
	unsigned int	s_color;
	unsigned int	e_color;
	unsigned int	cstart;
	unsigned int	cend;
	double			ratio;
	int				mn_z;
	int				mx_z;
	int				n;
	int				m;
	t_pos			**pos;
	t_pos			**s_pos;
	double			alpha;
	double			beta;
	double			incr_a;
	double			incr_b;
	int				size;
	int				med_z;
	int				r;
	int				g;
	int				b;
	int				max_r;
	int				max_g;
	int				max_b;
	int				offset;
}	t_data;

typedef struct s_color {
	double	cs;
	double	ce;
}	t_color;

int				parse_map(t_data *data, char *path);
void			init_data(t_data *data);
void			set_scale(t_data *data);
void			draw_image(t_data *data);
void			draw_line(t_pos *p1, t_pos *p2, t_data *data);
void			setup_line(t_pos *p1, t_pos *p2, t_line *line);
int				render_frame(void *void_data);
int				free_all(t_data *data);
void			fade(t_data *data);
void			update_pos(t_data *data);
int				get_dimension(t_data *data, char *path);
void			set_zero(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	get_trgb(int t, int r, int g, int b);
int				ft_abs(int n);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				ft_atoi(char *str);
int				key_hook(int keycode, void *void_data);
int				get_mouse_pos(int x, int y, void *void_data);
void			draw_color_line(t_pos *p1, t_pos *p2, t_data *data,
					t_color *color);
int				parse_line(t_data *data, char *cur, int idx);

#endif