/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:37:44 by ann               #+#    #+#             */
/*   Updated: 2022/04/30 13:01:56 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, unsigned int color, t_main *s)
{
	if (x > 0 && x < WINDOW_X && y > 0 && y < WINDOW_Y)
	{
		*((unsigned int *)(s->image_address + (x * (s->bpp / 8)) + \
		(y * s->size_line))) = color;
	}
}

void	draw_rect(int width, int height, t_coord const *origin, t_main *s)
{
	int	width_index;
	int	height_index;

	height_index = -1;
	while (++height_index < height)
	{
		width_index = -1;
		while (++width_index < width)
			put_pixel(origin->x + width_index, origin->y + height_index, \
			HX_WHITE, s);
	}
}
