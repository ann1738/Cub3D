/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_celling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:32:21 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/16 17:48:16 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_n_celling_cast(t_main *s)
{
	int			y;
	t_v_cast	v;

	ft_bzero(&v, sizeof(t_v_cast));
	v.x_direction = cos(s->player_angle);
	v.y_direction = sin(s->player_angle);
	y = 0;
	while (y < (WINDOW_Y / 2))
	{
		v.max_x_ray_dir = v.x_direction + s->camera_plane.x;
		v.min_x_ray_dir = v.x_direction - s->camera_plane.x;
		v.max_y_ray_dir = v.y_direction + s->camera_plane.y;
		v.min_y_ray_dir = v.y_direction - s->camera_plane.y;
		v.new_y_pos = y - (WINDOW_Y / 2);
		v.v_camera_pos = 0.5 * WINDOW_Y;
		v.row_distance = v.v_camera_pos / v.new_y_pos;

	}
}
