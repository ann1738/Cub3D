/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/18 14:11:58 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to draw player icon */

static void	draw_player_icon(t_main *s)
{
	t_coord	temp;

	/* draw player icon */
	temp.x = MINIMAP_X / 2 + MINI_OFFSET_X;
	temp.y = MINIMAP_Y / 2 + MINI_OFFSET_Y;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
}

/* function to make a section of the screen transparent with a color */

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
			new_color = *((unsigned int *)(s->image_address + \
			(s->size_line * (origin->y + height_index))) + \
			((origin->x + width_index) /* (s->bpp / 8)*/));
			new_color = add_fog_uint(0.8, color, new_color);
			put_pixel(origin->x + width_index, origin->y + height_index, \
			new_color, s);
		}
	}
}

/* function to draw rectangle but checks if the rectangle is outside the */
/* minimap boundaries */

static void	draw_mini_rect(int width, int height, t_coord const *origin, t_main *s)
{
	int	width_index;
	int	height_index;

	height_index = -1;
	while (++height_index < height)
	{
		width_index = -1;
		while (++width_index < width)
		{
			if (origin->x + width_index >= MINIMAP_X + MINI_OFFSET_X \
			|| origin->x + width_index <= MINI_OFFSET_X \
			|| origin->y + height_index >= MINIMAP_Y + MINI_OFFSET_Y \
			|| origin->y + height_index <= MINI_OFFSET_Y)
				continue ;
			put_pixel(origin->x + width_index, origin->y + height_index, \
			origin->color, s);
		}
	}
}

/* function to check if point (x,y) is outside of minimap */

bool	check_outside_minimap(int x, int y)
{
	if (x >= MINIMAP_X + MINI_OFFSET_X || x <= MINI_OFFSET_X \
	|| y >= MINIMAP_Y + MINI_OFFSET_Y || y <= MINI_OFFSET_Y)
		return (true);
	return (false);
}

/* function to draw minimap */

void	draw_minimap(t_main *s)
{
	int		x;
	int		y;
	t_coord	temp;

	/* draw transparent background */
	temp.x = MINI_OFFSET_X;
	temp.y = MINI_OFFSET_Y;
	make_rect_trans(MINIMAP_X, MINIMAP_Y, &temp, &s->minimap_color, s);
	/* draw rectangles of specific color for each number in the map */
	y = s->player_map_position.y - MINI_BLOCKS_AROUND - 1; //starting from the right place instead of looping extra times
	if (y < -1)
		y = -1;
	while (++y < s->map_height)
	{
		x = s->player_map_position.x - MINI_BLOCKS_AROUND - 1;
		if (x < -1)
			x = -1;
		while (s->map[y][++x])
		{
			if (s->map[y][x] == '1' \
			&& ((fabs(s->player_position.x - x) <= MINI_BLOCKS_AROUND + 1) && (fabs(s->player_position.y - y) <= MINI_BLOCKS_AROUND + 1)))
			{
				temp.x = ((((MINIMAP_X / 2) + MINI_OFFSET_X) + ((x - s->player_position.x) * MINI_BLOCK_SIZE_X)));
				temp.y = (((MINIMAP_Y / 2) + MINI_OFFSET_Y) + ((y - s->player_position.y) * MINI_BLOCK_SIZE_Y));
				temp.color = MINI_WALL_COLOR;
				draw_mini_rect(MINI_BLOCK_SIZE_X, MINI_BLOCK_SIZE_Y, &temp, s);
			}		
		}
	}
	draw_player_icon(s);
	temp.x = MINI_OFFSET_X;
	temp.y = MINI_OFFSET_Y;
	temp.color = MINI_WALL_BORDER;
	draw_border(MINIMAP_X, MINIMAP_Y, &temp, s);
}
