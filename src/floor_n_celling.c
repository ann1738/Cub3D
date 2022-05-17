/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_celling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:32:21 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/17 18:01:37 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_by_line(int img_y, t_v_cast *v, t_texture *tex, t_main *s)
{
	int				img_x;
	unsigned int	color;

	img_x = -1;
	while (++img_x < WINDOW_X)
	{
		color = *((unsigned int *)(tex->image_address + ((tex->size_line * (v->texture_y))) + (((v->texture_x + img_x) & tex->width - 1) * (tex->bpp / 8))));
		color = (color >> 1) & 8355711;
		// put_pixel(img_x, img_y, color, s);
		if (img_x >= 0 && img_x <= WINDOW_X && img_y >= 0 && img_y <= WINDOW_Y)
		{
			*((unsigned int *)(s->image_address + (img_x * (s->bpp / 8)) + \
			(img_y * s->size_line))) = color;
		}
		v->texture_x += v->step_x;
	}
}

void	sky_cast(t_main *s, t_texture *sky)
{
	int			y;
	t_v_cast	v;

	ft_bzero(&v, sizeof(t_v_cast));
	v.x_direction = cos(s->player_angle);
	v.y_direction = sin(s->player_angle);
	y = -1;
	while (++y < (WINDOW_Y / 2))
	{
		v.max_x_ray_dir = v.x_direction + s->camera_plane.x;
		v.min_x_ray_dir = v.x_direction - s->camera_plane.x;
		v.max_y_ray_dir = v.y_direction + s->camera_plane.y;
		v.min_y_ray_dir = v.y_direction - s->camera_plane.y;

		v.new_y_pos = y - (WINDOW_Y / 2);
		v.v_camera_pos = 0.5 * WINDOW_Y;
		v.row_distance = v.v_camera_pos / v.new_y_pos;

		v.step_x = (v.row_distance * (v.max_x_ray_dir - v.min_x_ray_dir)) / WINDOW_X;
		v.step_y = (v.row_distance * (v.max_y_ray_dir - v.min_y_ray_dir)) / WINDOW_X;
		
		v.x = s->player_position.x + (v.row_distance * v.min_x_ray_dir);
		v.y = s->player_position.y + (v.row_distance * v.min_y_ray_dir);

		v.texture_x = (int)(sky->width * (v.x - (int)v.x)) & (sky->width - 1);
		v.texture_y = (int)(sky->height * (v.y - (int)v.y)) & (sky->height - 1);

		v.x += v.step_x;
		v.y += v.step_y;
		
		draw_line_by_line(y, &v, sky, s);
	}
}

void	ground_cast(t_main *s, t_texture *sky)
{
	int			y;
	t_v_cast	v;

	ft_bzero(&v, sizeof(t_v_cast));
	y = WINDOW_Y / 2;
	v.x_direction = cos(s->player_angle);
	v.y_direction = sin(s->player_angle);
	while (y++ < WINDOW_Y)
	{
		v.max_x_ray_dir = v.x_direction + s->camera_plane.x;
		v.min_x_ray_dir = v.x_direction - s->camera_plane.x;
		v.max_y_ray_dir = v.y_direction + s->camera_plane.y;
		v.min_y_ray_dir = v.y_direction - s->camera_plane.y;

		v.new_y_pos = y - (WINDOW_Y / 2);
		v.v_camera_pos = 0.5 * WINDOW_Y;
		v.row_distance = v.v_camera_pos / v.new_y_pos;

		v.step_x = (v.row_distance * (v.max_x_ray_dir - v.min_x_ray_dir)) / WINDOW_X;
		v.step_y = (v.row_distance * (v.max_y_ray_dir - v.min_y_ray_dir)) / WINDOW_X;

		v.x = s->player_position.x + (v.row_distance * v.min_x_ray_dir);
		v.y = s->player_position.y + (v.row_distance * v.min_y_ray_dir);

		v.texture_x = (int)(sky->width * (v.x - (int)v.x)) & (sky->width - 1);
		v.texture_y = (int)(sky->height * (v.y - (int)v.y)) & (sky->height - 1);

		v.x += v.step_x;
		v.y += v.step_y;

		draw_line_by_line(y, &v, sky, s);
	}
}
