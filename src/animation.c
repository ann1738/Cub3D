/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:58:25 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/27 13:06:28 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//change function name
bool	check_sprite_coord(t_main *s, int x, int y)
{
	int	i;

	i = -1;
	while (++i < s->sprite->in_screen_count)
	{
		if (s->sprite->position[i].x == x && s->sprite->position[i].y == y)
			return (true);
	}
	return (false);
}

void	draw_sprite(t_main *s, t_texture *tex)
{
	int		x;
	int		y;
	int		d;
	t_coord	texture;

	x = s->sprite->x_start_draw - 1;
	while (++x < s->sprite->x_end_draw)
	{
		texture.x = (int)(256 * (x - (-s->sprite->sprite_w / 2 + \
		s->sprite->sprite_screen_x)) * tex->width / s->sprite->sprite_w) / 256;
		if (s->sprite->trans_y > 0 && x > 0 && x < WINDOW_X && \
		s->sprite->trans_y < s->sprite->z_buffer[x])
		{
			y = s->sprite->y_start_draw - 1;
			while (++y < s->sprite->y_end_draw)
			{
				d = (y) * 256 - WINDOW_Y * 128 + s->sprite->sprite_h * 128;
				texture.y = ((d * tex->height) / s->sprite->sprite_h) / 256;
				texture.color = *((unsigned int *)(tex->image_address + \
				(tex->size_line * texture.y) + (texture.x * (tex->bpp / 8))));
				if ((texture.color & 0x00FFFFFF) != 0)
					put_pixel(x, y, texture.color, s);
			}
		}
	}
}

int	animation(t_main *s)
{
	static double	i = 0;

	if (!s->sprite->in_screen_count)
		return (0);
	s->leaf_index = (int)i;
	redraw_window(s);
	usleep(10000);
	i += 0.2;
	if (i >= 8)
		i = 0;
	return (0);
}
