/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:02:48 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/15 19:18:33 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_door_vertical_texture(t_coord origin, int width, int height, t_texture const *tex, t_main *s) 
{
	int	width_index;
	int	height_index;

	height_index = -1;
	while (++height_index < height)
	{
		width_index = -1;
		while (++width_index < width)
		{
			origin.color =  *((unsigned int *)(tex->image_address + (tex->size_line * (int)s->texture_y) + \
							(((s->texture_x + width_index) & tex->width - 1) * (tex->bpp / 8))));
			put_pixel(origin.x + width_index, origin.y + height_index, origin.color, s);
		}
		s->texture_y += s->step_texture;
	}
}

void	draw_door(t_main *s)
{
	t_coord	origin;
	int		texture_index;

	s->there_is_a_door = false;
	texture_index = 4;
	//calculate the perpendicular door distance (to avoid fisheye)
	s->perpend_door_dist = s->door_final_side_length * fabs(cos(fabs(s->player_angle - atan2(s->ray_direction.y, s->ray_direction.x))));
	if (s->perpend_door_dist > s->depth)
		return ;
	if (s->perpend_door_dist < 2.0)	
		s->door_height = WINDOW_Y;
	else
		s->door_height = WALL_SCALE_FACTOR * WINDOW_Y / (s->perpend_door_dist);
	
	if (s->door_side_hit == SIDE_X)
		s->door_hit_pos = s->player_position.y + s->perpend_door_dist * s->ray_direction.y;
	else
		s->door_hit_pos = s->player_position.x + s->perpend_door_dist * s->ray_direction.x;
	s->door_hit_pos = s->door_hit_pos - floor(s->door_hit_pos);//to get the fraction

	s->texture_x = (int)(s->door_hit_pos * s->texture[texture_index].width);
	s->texture_x = s->texture[texture_index].width - s->texture_x - 1;
	
	s->step_texture = s->texture[texture_index].height / (double)s->door_height;
	s->texture_y = 0;

	origin.x = s->place_wall_at_x;
	origin.y = (WINDOW_Y / 2.0) - (s->door_height / 2.0);
	// origin.color = HX_PURPLE;
	draw_door_vertical_texture(origin, s->wall_width, s->door_height, &s->texture[texture_index], s);
}
