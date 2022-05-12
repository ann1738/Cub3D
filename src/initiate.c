/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:12:30 by anasr             #+#    #+#             */
/*   Updated: 2022/05/11 16:41:59 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	specific_player_info(int x, int y, double start_angle, t_main *s)
{
	//initiate player position
	s->player_position.x = x + 0.5;
	s->player_position.y = y + 0.5;
	s->player_map_position.x = x;
	s->player_map_position.y = y;
	//player direction
	// s->player_direction.x = 0;
	// s->player_direction.y = 1;
	s->player_angle = start_angle;
	// intialize camera plane * cos() and sin() are flipped bec camera_plane is perpendicular to the player_direction vector
	s->camera_plane.x = tan(deg_to_rad(FOV_DEG / 2.0)) * sin(s->player_angle);
	s->camera_plane.y = tan(deg_to_rad(FOV_DEG / 2.0)) * cos(s->player_angle);
}
void	initiate_player_info(t_main *s)
{
	int x;
	int y;
	int check;

	//loop through the map and draw a rectangle whenever "1" is there
	check = 0;
	y = -1;
	while(++y < s->map_height)
	{
		x = -1;
		while (++x < s->map_width && s->map[y][x])
		{
			if (s->map[y][x] == 'N' && (check++) >= 0)
				specific_player_info(x, y, NORTH, s);
			else if (s->map[y][x] == 'S' && (check++) >= 0)
				specific_player_info(x, y, SOUTH, s);
			else if (s->map[y][x] == 'W' && (check++) >= 0) //west and east mess up the arrow keys rotations
				specific_player_info(x, y, WEST, s);
			else if (s->map[y][x] == 'E' && (check++) >= 0)
				specific_player_info(x, y, EAST, s);
			if (check != 0)
				return ;
		}
	}
}