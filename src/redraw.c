/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:44:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/20 18:54:05 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to draw everything in the image and put into the window */

void	redraw_window(t_main *s)
{

	/* clear window */
	ft_bzero(s->image_address, s->size_line * WINDOW_Y);

	// printf("%shiii %d%s\n", PURPLE1, s->sprite->in_screen_count, RESET);
	/* draw floor and ceiling */
	draw_ceiling(s->ceiling_color, &s->fog, s);
	draw_floor(s->floor_color, &s->fog, s);
	// printf("%shiii %d%s\n", BLUE1, s->sprite->in_screen_count, RESET);

	// printf("BEFORE RAYCAST\n");

	// printf("BEFORE HAHAHAHAH, %d \n", s->sprite->in_screen_count);
	/* cast rays */
	cast_rays(s);
	// printf("AFTER RAYCAST\n");
	// printf("HAHAHAHAH, %d \n", s->sprite->in_screen_count);

	// printf("%shiii%s\n", PURPLE1, RESET);
	// printf("%shiii%s\n", BLUE1, RESET);
	/* sprite */
	// if (s->p->full_sprite_count)
	// 	sprite_cast(s);

	/* minimap drawing */
	if (s->minimap_on)
		draw_minimap(s);

	/* putting the image to the window */
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
}

