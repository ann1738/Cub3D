/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:44:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/10 15:36:56 by anasr            ###   ########.fr       */
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
	if (s->minimap_on)
		update_minimap(s);
	cast_rays(s);
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
}