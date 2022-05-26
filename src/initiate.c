/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:12:30 by anasr             #+#    #+#             */
/*   Updated: 2022/05/26 16:49:10 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	specific_player_info(int x, int y, double start_angle, t_main *s)
{
	s->player_position.x = x + 0.5;
	s->player_position.y = y + 0.5;
	s->player_map_position.x = x;
	s->player_map_position.y = y;
	s->player_angle = start_angle;
	s->camera_plane.x = tan(deg_to_rad(FOV_DEG / 2.0)) \
	* sin(s->player_angle);
	s->camera_plane.y = tan(deg_to_rad(FOV_DEG / 2.0)) \
	* (-cos(s->player_angle));
}

/* initiate the orientation and position of the player from the map */
void	initiate_player_info(t_main *s)
{
	int	x;
	int	y;
	int	check;

	check = 0;
	y = -1;
	while (++y < s->map_height)
	{
		x = -1;
		while (++x < s->map_width_max && s->map[y][x])
		{
			if (s->map[y][x] == 'N' && (check++) >= 0)
				specific_player_info(x, y, NORTH, s);
			else if (s->map[y][x] == 'S' && (check++) >= 0)
				specific_player_info(x, y, SOUTH, s);
			else if (s->map[y][x] == 'W' && (check++) >= 0)
				specific_player_info(x, y, WEST, s);
			else if (s->map[y][x] == 'E' && (check++) >= 0)
				specific_player_info(x, y, EAST, s);
			if (check != 0)
				return ;
		}
	}
}
