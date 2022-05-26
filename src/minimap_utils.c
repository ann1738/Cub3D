/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:08:20 by anasr             #+#    #+#             */
/*   Updated: 2022/05/26 17:36:59 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to make a section of the screen transparent with a color */
void	make_rect_trans(int *width_height, t_coord const *origin, \
t_color *color, t_main *s)
{
	unsigned int	new_color;
	int				width_index;
	int				height_index;

	height_index = -1;
	while (++height_index < width_height[1])
	{
		width_index = -1;
		while (++width_index < width_height[0])
		{
			new_color = *((unsigned int *)(s->image_address + \
			(s->size_line * (origin->y + height_index))) + \
			(origin->x + width_index));
			new_color = add_fog_uint(0.8, color, new_color);
			put_pixel(origin->x + width_index, origin->y + height_index, \
			new_color, s);
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
