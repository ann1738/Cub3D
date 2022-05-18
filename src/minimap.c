/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/17 23:30:57 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player_icon(t_main *s)
{
	t_coord temp;

	/* draw player icon */
	temp.x = MINIMAP_X / 2 + MINI_OFFSET_X; 
	temp.y = MINIMAP_Y / 2 + MINI_OFFSET_Y;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
	// printf("PLAYER(%d, %d)\n", 	s->player_map_position.x, s->player_map_position.y);
	
	/* temporary line to show the player's direction */
	// t_coord end;
	// end.x = temp.x + (30 * cos(s->player_angle + deg_to_rad(FOV_DEG / 2)));
	// end.y = temp.y + (30 * sin(s->player_angle + deg_to_rad(FOV_DEG / 2)));
	// temp.color = RAY_COLOR;
	// draw_line(temp, end, s);
	// end.x = temp.x + (30 * cos(s->player_angle - deg_to_rad(FOV_DEG / 2)));
	// end.y = temp.y + (30 * sin(s->player_angle - deg_to_rad(FOV_DEG / 2)));
	// draw_line(temp, end, s);
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

bool	check_outside_minimap(int x, int y)
{
	if (x >= MINIMAP_X + MINI_OFFSET_X || x <= MINI_OFFSET_X || y >= MINIMAP_Y + MINI_OFFSET_Y || y <= MINI_OFFSET_Y)
		return (true);
	return (false);
}

void	draw_mini_rect(int width, int height, t_coord const *origin, t_main *s)
{
	int	width_index;
	int	height_index;

	height_index = -1;
	while (++height_index < height)
	{
		width_index = -1;
		while (++width_index < width)
		{
			if (origin->x + width_index >= MINIMAP_X + MINI_OFFSET_X || origin->x + width_index <= MINI_OFFSET_X || origin->y + height_index >= MINIMAP_Y + MINI_OFFSET_Y || origin->y + height_index <= MINI_OFFSET_Y)
				continue ;
			put_pixel(origin->x + width_index, origin->y + height_index, \
			origin->color, s);
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
	int i = 0;
	/* draw rectangles of specific color for each number in the map */
	y = -1;
	while(++y < s->map_height)
	{
		x = -1;
		while (/*++x < s->map_width_max &&*/ s->map[y][++x])
		{
			if (s->map[y][x] == '1' 
			&& ((fabs(s->player_position.x - x) <= MINI_BLOCKS_AROUND + 1) && (fabs(s->player_position.y - y) <= MINI_BLOCKS_AROUND + 1)))
			{
				printf("minimap %d\n", i++);
				temp.x = ((((MINIMAP_X / 2) + MINI_OFFSET_X) + ((x - s->player_position.x) * MINI_BLOCK_SIZE_X))) + 1;
				temp.y = (((MINIMAP_Y / 2) + MINI_OFFSET_Y) + ((y - s->player_position.y) * MINI_BLOCK_SIZE_Y)) + 1;
				temp.color = MINI_WALL_COLOR;
				draw_mini_rect(MINI_BLOCK_SIZE_X - 1, MINI_BLOCK_SIZE_Y - 1, &temp, s);	
			}		
		}
	}
	// 	y = -7;
	// 	x = -6;
	// while(++y < 7 && s->map[s->player_map_position.y + y][x + s->player_map_position.x])
	// {
	// 	x = -7;
	// 	while (++x < 7 && s->map[s->player_map_position.y + y][x + s->player_map_position.x])
	// 	{
	// 		if (s->map[s->player_map_position.y + y][s->player_map_position.x + x] == '1') /*
	// 		&& ((fabs(s->player_position.x - x) <= MINI_BLOCKS_AROUND + 1) && (fabs(s->player_position.y - y) <= MINI_BLOCKS_AROUND + 1)))*/
	// 		{
	// 			printf("minimap %d\n", i++);
	// 			temp.x = (((MINIMAP_X / 2) + MINI_OFFSET_X) + (x * MINI_BLOCK_SIZE_X));
	// 			temp.y = (((MINIMAP_Y / 2) + MINI_OFFSET_Y) + (y * MINI_BLOCK_SIZE_Y));
	// 			temp.color = MINI_WALL_COLOR;
	// 			draw_rect(MINI_BLOCK_SIZE_X, MINI_BLOCK_SIZE_Y, &temp, s);	
	// 		}		
	// 	}
	// }
	draw_player_icon(s);
	temp.x = MINI_OFFSET_X;
	temp.y = MINI_OFFSET_Y;
	temp.color = MINI_WALL_BORDER;
	draw_border(MINIMAP_X, MINIMAP_Y, &temp, s);
	// draw_border(s->mini_width_unit * s->map_width_max, s->mini_height_unit * s->map_height, &temp, s);
}
