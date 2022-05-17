/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/17 18:14:17 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player_icon(t_main *s)
{
	t_coord temp;

	/* draw player icon */
	temp.x = (s->player_position.x * s->mini_width_unit) + MINI_OFFSET_X; 
	temp.y = (s->player_position.y * s->mini_height_unit) + MINI_OFFSET_Y;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
	// printf("PLAYER(%d, %d)\n", 	s->player_map_position.x, s->player_map_position.y);
	
	/* temporary line to show the player's direction */
	t_coord end;
	end.x = temp.x + (10 * cos(s->player_angle));
	end.y = temp.y + (10 * sin(s->player_angle));
	temp.color = RAY_COLOR;
	draw_line(temp, end, s);
}


static void	make_rect_trans(int width, int height, t_coord const *origin, t_color *color, t_main *s)
{
	unsigned int	new_color;
	int				width_index;
	int				height_index;

	height_index = -1;
	while (++height_index < height)
	{
		width_index = -1;
		while (++width_index < width)
		{
			new_color = *((unsigned int *)(s->image_address + (s->size_line * (origin->y + height_index))) + \
				((origin->x + width_index) /* (s->bpp / 8)*/));
			new_color = add_fog_uint(0.8, color, new_color);
			put_pixel(origin->x + width_index, origin->y + height_index, new_color, s);
		}
	}
}

/* function to draw minimap */

void	draw_minimap(t_main *s)
{
	int x;
	int y;
	t_coord temp;

	/* draw transparent background */
	temp.x = MINI_OFFSET_X;
	temp.y = MINI_OFFSET_Y;
	make_rect_trans(MINIMAP_X, MINIMAP_Y, &temp, &s->minimap_color, s);
	
	/* draw rectangles of specific color for each number in the map */
	y = -1;
	while(++y < s->map_height)
	{
		x = -1;
		while (/*++x < s->map_width_max &&*/ s->map[y][++x])
		{
			temp.x = (x * s->mini_width_unit) + MINI_OFFSET_X;
			temp.y = (y * s->mini_height_unit) + MINI_OFFSET_Y;
			temp.color = MINI_WALL_COLOR;
			if (s->map[y][x] == '1')
			{
				draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
				// temp.color = MINI_WALL_BORDER;
				// draw_border(s->mini_width_unit, s->mini_height_unit, &temp, s);
			}
			// else if (s->map[y][x] != ' ')
			// {
				// temp.color = HX_WHITE;
				// ++temp.x; //for borders
				// ++temp.y; //for borders
				// draw_rect(s->mini_width_unit, s->mini_height_unit, &temp, s);
			// }
		}
	}
	draw_player_icon(s);
	temp.x = MINI_OFFSET_X;
	temp.y = MINI_OFFSET_Y;
	temp.color = MINI_WALL_BORDER;
	draw_border(MINIMAP_X, MINIMAP_Y, &temp, s);
	// draw_border(s->mini_width_unit * s->map_width_max, s->mini_height_unit * s->map_height, &temp, s);
}
