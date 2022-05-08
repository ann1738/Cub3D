/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/08 23:26:29 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_n_draw_player(int x, int y, t_main *s)
{
	t_coord	temp;

	s->player_position.x = x + 0.5;
	s->player_position.y = y + 0.5;
	s->player_map_position.x = x;
	s->player_map_position.y = y;
	//player direction
	s->player_direction.x = 0;
	s->player_direction.y = 1;
	s->player_angle = M_PI * 0.75;
	temp.x = s->player_position.x * s->mini_width_unit; 
	temp.y = s->player_position.y * s->mini_height_unit;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
	// intialize camera plane *
	s->camera_plane.x = 0;
	s->camera_plane.y = 0.66;
}

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
		while (++x < s->map_width)
		{
			temp.x = x * s->mini_width_unit + 1;
			temp.y = y * s->mini_height_unit + 1;
			temp.color = MINI_WALL_COLOR;
			//to comply with norm either make function that has cases or one that uses function pointers
			if (s->map[y][x] == '1')
				draw_rect(s->mini_width_unit - 1, s->mini_height_unit - 1, &temp, s);
			else if (s->map[y][x] == '0')
			{
				temp.color = HX_WHITE;
				draw_rect(s->mini_width_unit - 1, s->mini_height_unit - 1, &temp, s);
			}
			else if (s->map[y][x] == 'N')
			{
				temp.color = HX_WHITE;
				draw_rect(s->mini_width_unit - 1, s->mini_height_unit - 1, &temp, s);
				//draw player icon
				init_n_draw_player(x, y, s);
			}
			printf("%d ", s->map[y][x]);
		}
		printf("\n");
	}
}

void	update_minimap(t_main *s)
{
	int x;
	int y;
	t_coord temp;

	//calculate the width and heigh unit length for drawing
	y = -1;
	while(++y < s->map_height)
	{
		x = -1;
		while (++x < s->map_width)
		{
			temp.x = x * s->mini_width_unit + 1;
			temp.y = y * s->mini_height_unit + 1;
			temp.color = MINI_WALL_COLOR;
			//to comply with norm either make function that has cases or one that uses function pointers
			if (s->map[y][x] == '1')
				draw_rect(s->mini_width_unit - 1, s->mini_height_unit - 1, &temp, s);
			else
			{
				temp.color = HX_WHITE;
				draw_rect(s->mini_width_unit - 1, s->mini_height_unit - 1, &temp, s);
			}
		}
	}
	//draw updated player icon
	temp.x = s->player_position.x * s->mini_width_unit; 
	temp.y = s->player_position.y * s->mini_height_unit;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
	s->player_map_position.x = (int)s->player_position.x;
	s->player_map_position.y = (int)s->player_position.y;
	cast_rays(s);
	s->player_map_position.x = (int)s->player_position.x;
	s->player_map_position.y = (int)s->player_position.y;

}
