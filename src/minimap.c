/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/10 15:32:16 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double deg)
{
	return(deg * (M_PI / 180.0));
}

// void	init_n_draw_player(int x, int y, double start_angle, t_main *s)
// {
// 	t_coord	temp;

// 	// s->player_position.x = x + 0.5;
// 	// s->player_position.y = y + 0.5;
// 	// s->player_map_position.x = x;
// 	// s->player_map_position.y = y;
// 	// //player direction
// 	// // s->player_direction.x = 0;
// 	// // s->player_direction.y = 1;
// 	// s->player_angle = start_angle;
// 	// // intialize camera plane * cos() and sin() are flipped bec camera_plane is perpendicular to the player_direction vector
// 	// s->camera_plane.x = tan(deg_to_rad(FOV_DEG / 2.0)) * sin(s->player_angle);
// 	// s->camera_plane.y = tan(deg_to_rad(FOV_DEG / 2.0)) * cos(s->player_angle);
// 	// printf("camera_plane.x = %lf, camera_plane.y = %lf\n", s->camera_plane.x, s->camera_plane.y);
// 	(void)x;
// 	(void)y;
// 	(void)start_angle;
// 	temp.x = s->player_position.x * s->mini_width_unit; 
// 	temp.y = s->player_position.y * s->mini_height_unit;
// 	temp.color = MINI_PLAYER_COLOR;
// 	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
// 	printf("PLAYER(%d, %d)\n", 	s->player_map_position.x, s->player_map_position.y);

// }

void	draw_minimap(t_main *s)
{
	int x;
	int y;
	t_coord temp;

	//calculate the width and heigh unit length for drawing
	if (s->map_width >= MINIMAP_X || s->map_height >= MINIMAP_Y) //if map is too big
		exit(write(STDERR_FILENO, "Error: Map is too big to be rendered\n", 37));
	s->mini_width_unit = round((double)MINIMAP_X / s->map_width);
	s->mini_height_unit = round((double)MINIMAP_Y / s->map_height);
	//loop through the map and draw a rectangle whenever "1" is there
	y = -1;
	while(++y < s->map_height)
	{
		x = -1;
		while (++x < s->map_width && s->map[y][x])
		{
			temp.x = x * s->mini_width_unit;
			temp.y = y * s->mini_height_unit;
			temp.color = MINI_WALL_COLOR;
			//to comply with norm either make function that has cases or one that uses function pointers
			if (s->map[y][x] == '1')
			{
				draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
				temp.color = MINI_WALL_BORDER;
				draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
			}
			else if (s->map[y][x] != ' ')
			{
				temp.color = HX_WHITE;
				draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
				temp.color = MINI_WALL_BORDER;
				draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
			}
			// if (s->map[y][x] == 'N')
			// 	init_n_draw_player(x, y, NORTH, s);
			// else if (s->map[y][x] == 'S')
			// 	init_n_draw_player(x, y, SOUTH, s);
			// else if (s->map[y][x] == 'W')
			// 	init_n_draw_player(x, y, WEST, s);
			// else if (s->map[y][x] == 'E')
			// 	init_n_draw_player(x, y, EAST, s);
		}
	}
	temp.x = s->player_position.x * s->mini_width_unit; 
	temp.y = s->player_position.y * s->mini_height_unit;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
}

void	update_minimap(t_main *s)
{
	int x;
	int y;
	t_coord temp;

	if (s->map_width >= MINIMAP_X || s->map_height >= MINIMAP_Y) //if map is too big
		exit(write(STDERR_FILENO, "Error: Map is too big to be rendered\n", 37));
	s->mini_width_unit = round((double)MINIMAP_X / s->map_width);
	s->mini_height_unit = round((double)MINIMAP_Y / s->map_height);
	//calculate the width and heigh unit length for drawing
	y = -1;
	while(++y < s->map_height)
	{
		x = -1;
		while (++x < s->map_width && s->map[y][x])
		{
			temp.x = x * s->mini_width_unit;
			temp.y = y * s->mini_height_unit;
			temp.color = MINI_WALL_COLOR;
			//to comply with norm either make function that has cases or one that uses function pointers
			if (s->map[y][x] == '1')
			{
				draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
				temp.color = MINI_WALL_BORDER;
				draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
			}
			else if (s->map[y][x] != ' ')
			{
				temp.color = HX_WHITE;
				draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
				temp.color = MINI_WALL_BORDER;
				draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
			}
		}
	}
	//draw updated player icon
	temp.x = s->player_position.x * s->mini_width_unit; 
	temp.y = s->player_position.y * s->mini_height_unit;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
	printf("PLAYER(%d, %d)\n", 	s->player_map_position.x, s->player_map_position.y);
	// cast_rays(s);
	// s->player_map_position.x = (int)s->player_position.x;
	// s->player_map_position.y = (int)s->player_position.y;
	// s->player_map_position.x = (int)s->player_position.x;
	// s->player_map_position.y = (int)s->player_position.y;
}
