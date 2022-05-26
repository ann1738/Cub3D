/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:54:22 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/26 17:00:53 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite_order(int *order, double *distance, int count)
{
	int		i;
	int		ii;
	double	temp;

	i = -1;
	while (++i < count)
	{
		ii = i;
		while (++ii < count)
		{
			if (distance[i] < distance[ii])
			{
				ft_swap(&order[i], &order[ii]);
				temp = distance[i];
				distance[i] = distance[ii];
				distance[ii] = temp;
			}
		}
	}
}

static void	get_sprite_dist_n_sort(t_main *s)
{
	int	i;

	s->sprite->s_order = ft_calloc_p(s->sprite->in_screen_count, sizeof(int));
	s->sprite->s_distance = ft_calloc_p(s->sprite->in_screen_count, \
	sizeof(double));
	i = -1;
	while (++i < s->sprite->in_screen_count)
	{
		s->sprite->s_order[i] = i;
		s->sprite->s_distance[i] = (\
		(s->player_position.x - s->sprite->position[i].x) * \
		(s->player_position.x - s->sprite->position[i].x) + \
		(s->player_position.y - s->sprite->position[i].y) * \
		(s->player_position.y - s->sprite->position[i].y));
	}
	sort_sprite_order(s->sprite->s_order, s->sprite->s_distance, \
	s->sprite->in_screen_count);
}

static void	get_start_n_end_drawing_coords(t_main *s)
{
	s->sprite->sprite_h = abs((int)((WINDOW_Y) / (s->sprite->trans_y)));
	s->sprite->y_start_draw = (-s->sprite->sprite_h / 2) + (WINDOW_Y / 2);
	if (s->sprite->y_start_draw < 0)
		s->sprite->y_start_draw = 0;
	s->sprite->y_end_draw = (s->sprite->sprite_h / 2) + (WINDOW_Y / 2);
	if (s->sprite->y_end_draw >= WINDOW_Y)
		s->sprite->y_end_draw = WINDOW_Y - 1;
	s->sprite->sprite_w = abs((int)(WINDOW_Y / (s->sprite->trans_y)));
	s->sprite->x_start_draw = -s->sprite->sprite_w / 2 + \
	s->sprite->sprite_screen_x;
	if (s->sprite->x_start_draw < 0)
		s->sprite->x_start_draw = 0;
	s->sprite->x_end_draw = s->sprite->sprite_w / 2 + \
	s->sprite->sprite_screen_x;
	if (s->sprite->x_end_draw >= WINDOW_X)
		s->sprite->x_end_draw = WINDOW_X - 1;
}

static void	get_position_n_avoid_fisheye(t_main *s, int i)
{
	s->sprite->current_sprite_pos.x = \
	(s->sprite->position[s->sprite->s_order[i]].x + 0.5) - s->player_position.x;
	s->sprite->current_sprite_pos.y = \
	(s->sprite->position[s->sprite->s_order[i]].y + 0.5) - s->player_position.y;
	s->sprite->invdet = \
	1 / (s->camera_plane.x * s->sprite->player_direction.y - \
	s->sprite->player_direction.x * s->camera_plane.y);
	s->sprite->trans_x = s->sprite->invdet * \
	(-s->sprite->player_direction.y * s->sprite->current_sprite_pos.x \
	+ s->sprite->player_direction.x * s->sprite->current_sprite_pos.y);
	s->sprite->trans_y = s->sprite->invdet * \
	(-s->camera_plane.y * s->sprite->current_sprite_pos.x + \
	s->camera_plane.x * s->sprite->current_sprite_pos.y);
	s->sprite->sprite_screen_x = (int)((WINDOW_X / 2) * \
	(1 + s->sprite->trans_x / s->sprite->trans_y));
}

void	sprite_cast(t_main *s, t_texture *tex)
{
	int	i;

	get_sprite_dist_n_sort(s);
	s->sprite->player_direction.x = cos(s->player_angle);
	s->sprite->player_direction.y = sin(s->player_angle);
	i = -1;
	while (++i < s->sprite->in_screen_count)
	{
		get_position_n_avoid_fisheye(s, i);
		get_start_n_end_drawing_coords(s);
		draw_sprite(s, tex);
	}
	free(s->sprite->s_order);
	free(s->sprite->s_distance);
}
