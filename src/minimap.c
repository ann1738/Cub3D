/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/07 20:59:27 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	background_color_minimap(unsigned int color, t_main *s)
// {
// 	t_coord temp;

// 	temp.x = 0;
// 	temp.y = 0;
// 	temp.color = color;
// 	draw_rect(MINIMAP_X - 2, MINIMAP_Y, &temp, s);	
// }

void	init_n_draw_player(int x, int y, t_main *s)
{
	s->player_position.x = (x * s->mini_width_unit) + (s->mini_width_unit / 2);
	s->player_position.y = (y * s->mini_height_unit) + (s->mini_height_unit / 2);
	s->player_position.color = MINI_PLAYER_COLOR;
	s->player_map_position.x = x;
	s->player_map_position.y = y;
	draw_circle(MINI_PLAYER_ICON_SIZE, &s->player_position, s);
}
void	draw_minimap(t_main *s)
{
	int x;
	int y;
	t_coord temp;

	//fill minimap with background color
	// background_color_minimap(MINI_BG_COLOR, s);
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
				s->player_direction.x = 0;
				s->player_direction.y = -1;
			}
		}
	}
	cast_rays(s);
}

void	update_minimap(t_main *s)
{
	int x;
	int y;
	t_coord temp;

	//fill minimap with background color
	// background_color_minimap(MINI_BG_COLOR, s);
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
		}
	}
	//draw updated player icon
	draw_circle(MINI_PLAYER_ICON_SIZE, &s->player_position, s);
	cast_rays(s);

}
