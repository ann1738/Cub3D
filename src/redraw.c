/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:44:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/17 13:49:00 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to draw everything in the image and put into the window */

void	redraw_window(t_main *s)
{
	/* clear window */
	ft_bzero(s->image_address, s->size_line * WINDOW_Y);

	/* draw floor and ceiling */
	draw_floor(s->ceiling_color, &s->fog, s);
	draw_ceiling(s->floor_color, &s->fog, s);

	/* cast rays */
	cast_rays(s);

	/* minimap drawing */
	if (s->minimap_on)
		draw_minimap(s);
	
	/* putting the image to the window */
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
}
