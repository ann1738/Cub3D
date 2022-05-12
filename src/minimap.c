/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/11 19:00:54 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				// temp.color = MINI_WALL_BORDER;
				// draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
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
	printf("map_width: %d\nmap_height: %d\n", s->map_width, s->map_height);
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
				++temp.x;
				++temp.y;
				draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
				// temp.color = MINI_WALL_BORDER;
				// draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
			}
		}
	}
	//draw updated player icon
	temp.x = s->player_position.x * s->mini_width_unit; 
	temp.y = s->player_position.y * s->mini_height_unit;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
	printf("PLAYER(%d, %d)\n", 	s->player_map_position.x, s->player_map_position.y);
	t_coord end;

	end.x = temp.x + (10 * cos(s->player_angle));
	end.y = temp.y + (10 * sin(s->player_angle));
	temp.color = RAY_COLOR;
	draw_line(temp, end, s);
	// cast_rays(s);
	// s->player_map_position.x = (int)s->player_position.x;
	// s->player_map_position.y = (int)s->player_position.y;
	// s->player_map_position.x = (int)s->player_position.x;
	// s->player_map_position.y = (int)s->player_position.y;
}
