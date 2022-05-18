/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:44:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/18 17:51:50 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to draw everything in the image and put into the window */

void	redraw_window(t_main *s)
{
	/* clear window */
	ft_bzero(s->image_address, s->size_line * WINDOW_Y);

	/* draw floor and ceiling */
	// draw_floor(s->ceiling_color, s);
	draw_ceiling(s->ceiling_color, s);
	// sky_cast(s, &s->texture[4]);
	ground_cast(s, &s->texture[5]);

	/* cast rays */
	cast_rays(s);

	/* minimap drawing */
	if (s->minimap_on)
		draw_minimap(s);

	// int	width, height;
	// int		bpp;
	// int		endian;
	// int		size_line;
	// void	*image = mlx_xpm_file_to_image(s->mlx, "redbrick.xpm", &width, &height);
	// char	*new_img_addr = mlx_get_data_addr(image, &bpp, &size_line, &endian);
	// printf("width: %d -- height: %d\n", width, height);
	// // ft_bzero(new_img_addr + (s->size_line * 32), 1000);
	// (void) new_img_addr;
	// unsigned int color;
	// double count = 0;
	// for (int j = 0; j < (64 * 4) - 1; j++)
	// {
	// 	for (int i = 0; i < 63; i++)
	// 	{
	// 		color =  *((unsigned int *)(new_img_addr + (size_line * (int)count) + (i * (bpp / 8))));
	// 		put_pixel(i, j, color, s);
	// 	}
	// 	count += 0.25;
	// }
	
	/* putting the image to the window */
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
}
