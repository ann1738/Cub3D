/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/07 20:59:55 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	d_abs(double x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	cast_rays(t_main *s)
{
	t_coord	temp;
	// initalize player's orientation

	// intialize camera plane
	s->camera_plane.x = 0;
	s->camera_plane.y = 0.66;
	//calculate camera_x and ray direction
	s->ray_direction.x = s->player_direction.x + s->camera_plane.x;
	s->ray_direction.y = s->player_direction.y + s->camera_plane.y;
	//calculate delta distances
	if (s->ray_direction.x != 0)
		s->delta_distance.x = d_abs(1 / s->ray_direction.x);
	else
		s->delta_distance.x = 10000000;
	if (s->ray_direction.y != 0)
		s->delta_distance.y = d_abs(1 / s->ray_direction.y);
	else
		s->delta_distance.y = 10000000;
	//
	if (s->ray_direction.x >= 0)
	{
		s->step.x = 1;
		s->side_distance.x = (((s->player_map_position.x + 1) * s->mini_width_unit) - s->player_position.x);
	}
	else
	{
		s->step.x = -1;
		s->side_distance.x = s->player_position.x - (s->player_map_position.x * s->mini_width_unit);
	}
	if (s->ray_direction.y >= 0)
	{
		s->step.y = 1;
		s->side_distance.y = (((s->player_map_position.y + 1) * s->mini_height_unit) - s->player_position.y);
	}
	else
	{
		s->step.y = -1;
		s->side_distance.y = s->player_position.y - (s->player_map_position.y * s->mini_height_unit);
	}
	while (s->map[s->player_map_position.y][s->player_map_position.x] != '1')
	{
		if (s->side_distance.x < s->side_distance.y)
		{
			s->side_distance.x += s->delta_distance.x;
			s->player_map_position.x += s->step.x;
		}
		else
		{
			s->side_distance.y += s->delta_distance.y;
			s->player_map_position.y += s->step.y;
		}
	}
	temp.x = s->side_distance.x;
	temp.y = s->side_distance.y;
	draw_line(s->player_position, temp, s);
}