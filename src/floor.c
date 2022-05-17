/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:32:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/17 13:09:56 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(unsigned int color, t_color *fog_color, t_main *s)
{
	double			step;
	double			intensity;
	unsigned int	new_color;
	int				width_index;
	int				height_index;

	intensity = 0;
	step = 1.0 / WINDOW_Y_2;
	new_color = color;
	height_index = -1;
	while (++height_index < WINDOW_Y_2)
	{
		width_index = -1;
		while (++width_index < WINDOW_X)
			put_pixel(width_index, WINDOW_Y - height_index, new_color, s);
		new_color = add_fog_uint(intensity, fog_color, color);
		intensity += step;
	}
}
