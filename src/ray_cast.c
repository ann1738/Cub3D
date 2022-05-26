/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 18:30:07 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* this function calculates the ray direction and delta distances */
static void	calc_ray_dir_n_delta_dist(t_main *s, double i)
{
	s->ray_direction.x = cos(s->player_angle) + (s->camera_plane.x * i);
	s->ray_direction.y = sin(s->player_angle) + (s->camera_plane.y * i);
	s->ray_map_position.x = s->player_map_position.x;
	s->ray_map_position.y = s->player_map_position.y;
	if (s->ray_direction.x != 0)
		s->delta_distance_x = sqrt(1 + \
		(s->ray_direction.y / s->ray_direction.x) * \
		(s->ray_direction.y / s->ray_direction.x));
	else
		s->delta_distance_x = 1e8;
	if (s->ray_direction.y != 0)
		s->delta_distance_y = sqrt(1 + \
		(s->ray_direction.x / s->ray_direction.y) * \
		(s->ray_direction.x / s->ray_direction.y));
	else
		s->delta_distance_y = 1e8;
}

/* function to calculate the inital ray length to reach the side of the next */
/* wall in terms of x and y */
static void	calc_inital_side_len(t_main *s)
{
	s->step.x = 0;
	s->step.y = 0;
	if (s->ray_direction.x >= 0 && (++s->step.x) >= 0)
		s->side_length_x = ((s->ray_map_position.x + 1) - s->player_position.x) \
		* s->delta_distance_x;
	else if ((--s->step.x) <= 0)
		s->side_length_x = (s->player_position.x - s->ray_map_position.x) * \
		s->delta_distance_x;
	if (s->ray_direction.y >= 0 && ((++s->step.y) >= 0))
		s->side_length_y = ((s->ray_map_position.y + 1) - \
		s->player_position.y) * s->delta_distance_y;
	else if ((--s->step.y) <= 0)
		s->side_length_y = (s->player_position.y - s->ray_map_position.y) * \
		s->delta_distance_y;
	if (s->side_length_x < s->side_length_y)
		s->final_side_length = s->side_length_x;
	else
		s->final_side_length = s->side_length_y;
}

/* function to draw walls based on line height */
static void	draw_wall(t_main *s)
{
	int		i;
	t_coord	origin;
	int		texture_index;
	int		width_height[2];

	select_correct_texture(&texture_index, s);
	s->perpend_wall_dist = s->final_side_length * fabs(cos(fabs(\
	s->player_angle - atan2(s->ray_direction.y, s->ray_direction.x))));
	i = -1;
	while (++i < s->wall_width)
		s->sprite->z_buffer[s->place_wall_at_x + i] = s->perpend_wall_dist;
	prepare_to_draw_wall(texture_index, s);
	select_fog_intensity(s);
	origin.x = s->place_wall_at_x;
	origin.y = (WINDOW_Y / 2.0) - (s->wall_height / 2.0);
	width_height[0] = s->wall_width;
	width_height[1] = s->wall_height;
	draw_vertical_texture(origin, width_height, &s->texture[texture_index], s);
}

static void	ray_casting_loop(t_main *s)
{
	while (s->final_side_length <= s->depth && \
	s->map[s->ray_map_position.y][s->ray_map_position.x] != '1')
	{
		if (s->side_length_x < s->side_length_y)
		{
			s->final_side_length = s->side_length_x;
			s->side_length_x += s->delta_distance_x;
			s->ray_map_position.x += s->step.x;
			s->side_hit = SIDE_X;
		}
		else
		{
			s->final_side_length = s->side_length_y;
			s->side_length_y += s->delta_distance_y;
			s->ray_map_position.y += s->step.y;
			s->side_hit = SIDE_Y;
		}
		if (s->ray_map_position.y > s->map_height - 1 \
		|| s->ray_map_position.x > s->map_width_max - 1)
		{
			s->final_side_length = s->depth;
			break ;
		}
		check_n_save_leaf_pos(s);
	}
}

/* primary function for raycasting */
void	cast_rays(t_main *s)
{
	double	i;
	double	step;

	s->sprite->in_screen_count = 0;
	s->dont_draw = false;
	i = 1;
	s->place_wall_at_x = 0;
	s->wall_width = WINDOW_X / NUMBER_OF_RAYS;
	step = 2.0 / NUMBER_OF_RAYS;
	while (i >= -1 && s->place_wall_at_x < WINDOW_X)
	{
		calc_ray_dir_n_delta_dist(s, i);
		calc_inital_side_len(s);
		ray_casting_loop(s);
		if (s->minimap_on)
			draw_rays_for_minimap(s);
		draw_wall(s);
		i -= step;
		s->place_wall_at_x += s->wall_width;
	}
}
