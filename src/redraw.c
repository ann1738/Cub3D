/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:44:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/12 12:58:00 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_window(t_main *s)
{
	//clear window
	ft_bzero(s->image_address, s->size_line * WINDOW_Y);
	//draw floor and ceiling
	draw_floor(FLOOR_COLOR, s);
	draw_ceiling(CEILING_COLOR, s);
	//draw minimap after movement or rotation
	cast_rays(s);
	if (s->minimap_on)
		update_minimap(s);
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
	// int width = 0, height = 0;
	// void	*image;
	// image = mlx_xpm_file_to_image(s->mlx, "redbrick.xpm", &width, &height);
	// mlx_put_image_to_window(s->mlx, s->mlx_window, image, 0, 0);
	printf("FPS: %lf", 1 / s->fps);
}