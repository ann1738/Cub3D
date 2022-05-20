/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:58:25 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/20 18:43:43 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_if_coord_exist(t_main *s, int x, int y)
{
	int	i;

	i = -1;
	while (++i < s->sprite->in_screen_count)
	{
		if (s->sprite->position[i].x == x && s->sprite->position[i].y == y)
		{
			return (true);
		}
	}
	printf("%shiii %d%s\n", GREEN1, s->sprite->in_screen_count, RESET);

	return (false);
}

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

void	draw_sprite(t_main *s)
{
	int	x;
	int	y;
	int d;
	t_coord texture;

	x = s->sprite->x_start_draw - 1;
	while (++x < s->sprite->x_end_draw)
	{
		texture.x = (int)(x - (-s->sprite->sprite_w / 2 + s->sprite->sprite_screen_x)) * s->texture[4].width / s->sprite->sprite_w;
		if (s->sprite->trans_y > 0 && x > 0 && x < WINDOW_X && s->sprite->trans_y < s->sprite->z_buffer[x])
		{
			y = s->sprite->y_start_draw - 1;
			while (++y < s->sprite->y_end_draw)
			{
				d = y - WINDOW_Y + s->sprite->sprite_h;
				texture.y = (d * s->texture[4].height) / s->sprite->sprite_h;
				texture.color = *((unsigned int *)(s->texture[4].image_address + (s->texture[4].size_line * texture.y) + (texture.x * (s->texture[4].bpp / 8))));
				put_pixel(x, y, texture.color, s);
			}
		}
	}
}

void	sprite_cast(t_main *s)
{
	int			i;
	int			*s_order;
	double		*s_distance;
	t_vector	current_sprite_pos;

	i = -1;
	printf("CAST, %d \n", s->sprite->in_screen_count);
	s_order = ft_calloc(s->sprite->in_screen_count, sizeof(int));
	if (!s_order)
	{
		printf("%sError: fatal error%s\n", RED2, RESET);
		exit(1);
	}
	s_distance = ft_calloc(s->sprite->in_screen_count, sizeof(int));
	if (!s_distance)
	{
		printf("%sError: fatal error%s\n", RED2, RESET);
		exit(1);
	}
	while (++i < s->sprite->in_screen_count)
	{
		s_order[i] = i;
		s_distance[i] = ((s->player_position.x - s->sprite->position[i].x) * (s->player_position.x - s->sprite->position[i].x)) + ((s->player_position.y - s->sprite->position[i].y) * (s->player_position.y - s->sprite->position[i].y));
	}
	sort_sprite_order(s_order, s_distance, s->sprite->in_screen_count);
	i = -1;
	while (++i < s->sprite->in_screen_count)
	{
		current_sprite_pos.x = s->sprite->position[i].x - s->player_position.x;
		current_sprite_pos.y = s->sprite->position[i].y - s->player_position.y;

		s->sprite->invdet = 1.0 / ((s->camera_plane.x * s->ray_direction.y) - (s->ray_direction.x * s->camera_plane.y));

		s->sprite->trans_x = s->sprite->invdet * (s->ray_direction.y * current_sprite_pos.x - s->ray_direction.x * current_sprite_pos.y);
		s->sprite->trans_y = s->sprite->invdet * (-s->camera_plane.y * current_sprite_pos.x + s->camera_plane.x * current_sprite_pos.y);

		s->sprite->sprite_screen_x = (int)((WINDOW_X / 2) * (1 + s->sprite->trans_x / s->sprite->trans_y));

		s->sprite->sprite_h = abs((int)(WINDOW_Y / (s->sprite->trans_y)));
		s->sprite->y_start_draw = -s->sprite->sprite_h / 2 + WINDOW_Y / 2;
		if (s->sprite->y_start_draw < 0)
			s->sprite->y_start_draw = 0;
		s->sprite->y_end_draw = s->sprite->sprite_h / 2 + WINDOW_Y / 2;
		if (s->sprite->y_end_draw >= WINDOW_Y)
			s->sprite->y_end_draw = WINDOW_Y - 1;
		
		s->sprite->sprite_w = abs((int)(WINDOW_X / (s->sprite->trans_x)));
		s->sprite->x_start_draw = -s->sprite->sprite_w / 2 + s->sprite->sprite_screen_x;
		if (s->sprite->x_start_draw < 0)
			s->sprite->x_start_draw = 0;
		s->sprite->x_end_draw = s->sprite->sprite_w / 2 + s->sprite->sprite_screen_x;
		if (s->sprite->x_end_draw >= WINDOW_X)
			s->sprite->x_end_draw = WINDOW_X - 1;

		draw_sprite(s);
		
	}

	// at the end
	free(s_order);
	free(s_distance);
	s->sprite->in_screen_count = 0;
}

// int animation(t_main *s)
// {
// 	;
// }