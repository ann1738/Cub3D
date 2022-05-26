/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_celling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:32:21 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/26 17:32:24 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_by_line(int y, t_v_cast *v, t_texture *tex, t_main *s)
{
	int				x;
	unsigned int	color;

	x = -1;
	while (++x < WINDOW_X)
	{
		v->texture_x = (int)(tex->width * (v->x - (int)v->x)) & (tex->width - 1);
		v->texture_y = (int)(tex->height * (v->y - (int)v->y)) & (tex->height - 1);

		color = *((unsigned int *)(tex->image_address + ((tex->size_line * (v->texture_y))) + (v->texture_x * (tex->bpp / 8))));

		// color = (color >> 1) & 8355711;

		put_pixel(x, y, color, s);
		v->x += v->step_x;
		v->y += v->step_y;
	}
}

// void	sky_cast(t_main *s, t_texture *sky)
// {
// 	int			y;
// 	t_v_cast	v;

// 	ft_bzero(&v, sizeof(t_v_cast));
// 	v.x_direction = cos(s->player_angle);
// 	v.y_direction = sin(s->player_angle);
// 	y = -1;
// 	while (++y < (WINDOW_Y / 2))
// 	{
// 		v.max_x_ray_dir = v.x_direction + s->camera_plane.x;
// 		v.min_x_ray_dir = v.x_direction - s->camera_plane.x;
// 		v.max_y_ray_dir = v.y_direction + s->camera_plane.y;
// 		v.min_y_ray_dir = v.y_direction - s->camera_plane.y;

// 		v.new_y_pos = y - (WINDOW_Y / 2);
// 		v.v_camera_pos = 0.5 * WINDOW_Y;
// 		v.row_distance = v.v_camera_pos / v.new_y_pos;

// 		v.step_x = (v.row_distance * (v.max_x_ray_dir - v.min_x_ray_dir)) / WINDOW_X;
// 		v.step_y = (v.row_distance * (v.max_y_ray_dir - v.min_y_ray_dir)) / WINDOW_X;
		
// 		v.x = s->player_position.x + (v.row_distance * v.min_x_ray_dir);
// 		v.y = s->player_position.y + (v.row_distance * v.min_y_ray_dir);

// 		v.texture_x = (int)(sky->width * (v.x - (int)v.x)) & (sky->width - 1);
// 		v.texture_y = (int)(sky->height * (v.y - (int)v.y)) & (sky->height - 1);

// 		v.x += v.step_x;
// 		v.y += v.step_y;
		
// 		draw_line_by_line(y, &v, sky, s);
// 	}
// }

void	color_ceiling(unsigned int color, t_color *fog_color, t_main *s)
{
	double			step;
	double			intensity;
	unsigned int	new_color;
	int				width_index;
	int				height_index;

	intensity = 0;
	step = 1.0 / WINDOW_Y_2;
	new_color = color;
	height_index = -1;
	while (++height_index < WINDOW_Y_2)
	{
		width_index = -1;
		while (++width_index < WINDOW_X)
			put_pixel(width_index, height_index, new_color, s);
		new_color = add_fog_uint(intensity, fog_color, color);
		intensity += step;
	}
}

void	color_floor(unsigned int color, t_color *fog_color, t_main *s)
{
	double			step;
	double			intensity;
	unsigned int	new_color;
	int				width_index;
	int				height_index;

	intensity = 0;
	step = 1.0 / WINDOW_Y_2;
	new_color = color;
	height_index = 0;
	while (++height_index <= WINDOW_Y_2)
	{
		width_index = -1;
		while (++width_index < WINDOW_X)
			put_pixel(width_index, WINDOW_Y - height_index, new_color, s);
		new_color = add_fog_uint(intensity, fog_color, color);
		intensity += step;
	}
}

void	floor_n_ceiling_cast(t_main *s, t_texture *texture, int y)
{
	int			limit;
	t_v_cast	v;

	ft_bzero(&v, sizeof(t_v_cast));
	limit = WINDOW_X / 2;
	if (y == (WINDOW_X / 2))
		limit = WINDOW_X;
	v.x_direction = cos(s->player_angle);
	v.y_direction = sin(s->player_angle);
	while (y < limit)
	{
		v.max_x_ray_dir = v.x_direction - s->camera_plane.x;
		v.min_x_ray_dir = v.x_direction + s->camera_plane.x;
		v.max_y_ray_dir = v.y_direction - s->camera_plane.y;
		v.min_y_ray_dir = v.y_direction + s->camera_plane.y;

		v.new_y_pos = y - (WINDOW_Y / 2);
		v.v_camera_pos = WINDOW_Y / 2;
		v.row_distance = v.v_camera_pos / v.new_y_pos;

		v.step_x = (v.row_distance * (v.max_x_ray_dir - v.min_x_ray_dir)) / WINDOW_X;
		v.step_y = (v.row_distance * (v.max_y_ray_dir - v.min_y_ray_dir)) / WINDOW_X;

		v.x = s->player_position.x + (v.row_distance * v.min_x_ray_dir);
		v.y = s->player_position.y + (v.row_distance * v.min_y_ray_dir);

		draw_line_by_line(y, &v, texture, s);
		y++;
	}
}
