/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:37:44 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 16:37:59 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to put pixels on the current image buffer */
void	put_pixel(int x, int y, unsigned int color, t_main *s)
{
	if (x >= 0 && x <= WINDOW_X && y >= 0 && y <= WINDOW_Y)
	{
		*((unsigned int *)(s->image_address + (x * (s->bpp / 8)) + \
		(y * s->size_line))) = color;
	}
}

/* draws filled rectangle with given width and height starting from a set of */
/* coordinates */
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
			origin->color, s);
	}
}

/* draws hollow rectangle with given width and height starting from a set of */
/* coordinates to act as a border */
void	draw_border(int width, int height, t_coord const *origin, t_main *s)
{
	int	width_index;
	int	height_index;

	height_index = -1;
	while (++height_index < height)
	{
		if (!height_index || height_index == height - 1)
		{
			width_index = -1;
			while (++width_index < width)
				put_pixel(origin->x + width_index, origin->y + height_index, \
				origin->color, s);
		}
		else
		{
			put_pixel(origin->x + 0, origin->y + height_index, \
			origin->color, s);
			put_pixel(origin->x + width, origin->y + height_index, \
			origin->color, s);
		}
	}
}

/* draws filled circle with given radius starting from a set of coordinates */
void	draw_circle(int radius, t_coord const *origin, t_main *s)
{
	double	angle;

	while (radius >= 0)
	{
		angle = 0;
		while (angle <= 360)
		{
			put_pixel(origin->x + (int)(radius * cos(angle)), \
			origin->y + (int)(radius * sin(angle)), origin->color, s);
			angle += 0.05;
		}
		--radius;
	}
}

/* draws filled vertical rectangle with given width and height starting from */
/* a set of coordinates */
void	draw_vertical_texture(t_coord origin, int *width_height, \
t_texture const *tex, t_main *s)
{
	int	width_index;
	int	height_index;

	height_index = -1;
	while (++height_index < width_height[1])
	{
		width_index = -1;
		while (++width_index < width_height[0])
		{
			origin.color = *((unsigned int *)(tex->image_address + \
			(tex->size_line * ((int)s->texture_y & (tex->height - 1))) + \
			(((s->texture_x + width_index) & (tex->width - 1)) * \
			(tex->bpp / 8))));
			if (s->fog_intensity)
				origin.color = add_fog_uint(s->fog_intensity, &s->fog, \
				origin.color);
			if ((origin.color & 0x00FFFFFF) != 0)
				put_pixel(origin.x + width_index, \
				origin.y + height_index, origin.color, s);
		}
		s->texture_y += s->step_texture;
	}
}
