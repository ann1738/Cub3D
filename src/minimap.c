/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:39:15 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 17:21:34 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to draw player icon */
static void	draw_player_icon(t_main *s)
{
	t_coord	temp;

	temp.x = MINIMAP_X / 2 + MINI_OFFSET_X;
	temp.y = MINIMAP_Y / 2 + MINI_OFFSET_Y;
	temp.color = MINI_PLAYER_COLOR;
	draw_circle(MINI_PLAYER_ICON_SIZE, &temp, s);
}

/* function to draw rectangle but checks if the rectangle is outside the */
/* minimap boundaries */
static void	draw_mini_rect(int width, int height, t_coord const *origin, \
t_main *s)
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

static void	draw_if_inside_minimap(int x, int y, t_coord *temp, t_main *s)
{
	if (s->map[y][x] == '1' \
	&& ((fabs(s->player_position.x - x) <= MINI_BLOCKS_AROUND + 1) \
	&& (fabs(s->player_position.y - y) <= MINI_BLOCKS_AROUND + 1)))
	{
		temp->x = ((((MINIMAP_X / 2) + MINI_OFFSET_X) + \
		((x - s->player_position.x) * MINI_BLOCK_SIZE_X)));
		temp->y = (((MINIMAP_Y / 2) + MINI_OFFSET_Y) + \
		((y - s->player_position.y) * MINI_BLOCK_SIZE_Y));
		temp->color = MINI_WALL_COLOR;
		draw_mini_rect(MINI_BLOCK_SIZE_X, MINI_BLOCK_SIZE_Y, temp, s);
	}		
}

static void	draw_mini_border(t_coord *temp, t_main *s)
{
	temp->x = MINI_OFFSET_X;
	temp->y = MINI_OFFSET_Y;
	temp->color = MINI_WALL_BORDER;
	draw_border(MINIMAP_X, MINIMAP_Y, temp, s);
}

/* function to draw minimap */
void	draw_minimap(t_main *s)
{
	int		x;
	int		y;
	t_coord	temp;
	int		width_height[2];

	temp.x = MINI_OFFSET_X;
	temp.y = MINI_OFFSET_Y;
	width_height[0] = MINIMAP_X;
	width_height[1] = MINIMAP_Y;
	make_rect_trans(width_height, &temp, &s->minimap_color, s);
	y = s->player_map_position.y - MINI_BLOCKS_AROUND - 1;
	if (y < -1)
		y = -1;
	while (++y < s->map_height)
	{
		x = s->player_map_position.x - MINI_BLOCKS_AROUND - 1;
		if (x < -1)
			x = -1;
		while (s->map[y][++x])
			draw_if_inside_minimap(x, y, &temp, s);
	}
	draw_player_icon(s);
	draw_mini_border(&temp, s);
}
