/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:37:34 by anasr             #+#    #+#             */
/*   Updated: 2022/05/26 19:08:45 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays_for_minimap(t_main *s)
{
	t_coord	start;
	t_coord	end;

	start.x = MINIMAP_X / 2 + MINI_OFFSET_X;
	start.y = MINIMAP_Y / 2 + MINI_OFFSET_Y;
	end.x = start.x + (s->final_side_length * MINI_BLOCK_SIZE_X * \
	cos(atan2(s->ray_direction.y, s->ray_direction.x)));
	end.y = start.y + (s->final_side_length * MINI_BLOCK_SIZE_Y * \
	sin(atan2(s->ray_direction.y, s->ray_direction.x)));
	draw_line(start, end, s);
}

void	select_fog_intensity(t_main *s)
{
	s->fog_intensity = 0;
	if (s->perpend_wall_dist <= s->depth / 2.0)
		s->fog_intensity = 0;
	else if (s->perpend_wall_dist <= s->depth / 1.9)
		s->fog_intensity = 0.1;
	else if (s->perpend_wall_dist <= s->depth / 1.8)
		s->fog_intensity = 0.2;
	else if (s->perpend_wall_dist <= s->depth / 1.7)
		s->fog_intensity = 0.3;
	else if (s->perpend_wall_dist <= s->depth / 1.6)
		s->fog_intensity = 0.4;
	else if (s->perpend_wall_dist <= s->depth / 1.5)
		s->fog_intensity = 0.5;
	else if (s->perpend_wall_dist <= s->depth / 1.4)
		s->fog_intensity = 0.6;
	else if (s->perpend_wall_dist <= s->depth / 1.3)
		s->fog_intensity = 0.7;
	else if (s->perpend_wall_dist <= s->depth / 1.2)
		s->fog_intensity = 0.8;
	else if (s->perpend_wall_dist <= s->depth / 1.1)
		s->fog_intensity = 0.9;
	else if (s->perpend_wall_dist <= s->depth / 1.0)
		s->fog_intensity = 1;
	else if (s->perpend_wall_dist > s->depth)
		s->fog_intensity = 1;
}

void	select_correct_texture(int *texture_index, t_main *s)
{
	*texture_index = 0;
	if (s->ray_direction.x > 0 && s->side_hit == SIDE_X)
		*texture_index = 3;
	else if (s->ray_direction.x < 0 && s->side_hit == SIDE_X)
		*texture_index = 2;
	else if (s->ray_direction.y > 0 && s->side_hit == SIDE_Y)
		*texture_index = 1;
	else if (s->ray_direction.y < 0 && s->side_hit == SIDE_Y)
		*texture_index = 0;
}

void	prepare_to_draw_wall(int texture_index, t_main *s)
{
	if (s->perpend_wall_dist != 0)
		s->wall_height = WALL_SCALE_FACTOR * WINDOW_Y / s->perpend_wall_dist;
	else
		s->wall_height = WINDOW_Y;
	s->step_texture = s->texture[texture_index].height / (double)s->wall_height;
	s->texture_y = 0;
	if (s->wall_height > WINDOW_Y)
	{
		s->texture_y = ((s->wall_height - WINDOW_Y) / 2.0) * s->step_texture;
		s->wall_height = WINDOW_Y;
	}	
	if (s->side_hit == SIDE_X)
		s->wall_hit_pos = s->player_position.y + \
		s->perpend_wall_dist * s->ray_direction.y;
	else
		s->wall_hit_pos = s->player_position.x + \
		s->perpend_wall_dist * s->ray_direction.x;
	s->wall_hit_pos = s->wall_hit_pos - floor(s->wall_hit_pos);
	s->offset = (int)(s->wall_hit_pos * s->texture[texture_index].width);
	s->texture_x = s->offset;
	if ((s->side_hit == SIDE_X && s->ray_direction.x > 0) || \
	(s->side_hit == SIDE_Y && s->ray_direction.y < 0))
		s->texture_x = s->texture[texture_index].width - s->texture_x - 1;
}

void	check_n_save_leaf_pos(t_main *s)
{
	if (s->map[s->ray_map_position.y][s->ray_map_position.x] == 'L' \
	&& !check_sprite_coord(s, s->ray_map_position.x, s->ray_map_position.y))
	{
		s->sprite->position[s->sprite->in_screen_count].x = \
		s->ray_map_position.x;
		s->sprite->position[s->sprite->in_screen_count].y = \
		s->ray_map_position.y;
		++s->sprite->in_screen_count;
	}
}
