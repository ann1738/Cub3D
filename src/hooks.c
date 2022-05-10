/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 02:29:56 by ann               #+#    #+#             */
/*   Updated: 2022/05/10 15:27:49 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//make this better.. it still doesn't work properly on open edges

bool	check_collision(double change_x, double change_y, t_main *s)
{
	t_vector temp_position;
	t_coord temp_map_position;
	double	temp_change;

	printf("%lf\n", MINI_PLAYER_ICON_SIZE / (double)s->mini_width_unit);
	if (change_x != 0)
	{
		if (change_x > 0)
			change_x += MINI_PLAYER_ICON_SIZE / (double)s->mini_width_unit;
		else if (change_x < 0)
			change_x -= MINI_PLAYER_ICON_SIZE / (double)s->mini_width_unit;
		change_y = MINI_PLAYER_ICON_SIZE / (double)s->mini_height_unit;
		temp_change = -MINI_PLAYER_ICON_SIZE / (double)s->mini_height_unit;
	}
	else
	{
		if (change_y > 0)
			change_y += MINI_PLAYER_ICON_SIZE / (double)s->mini_height_unit;
		else if (change_y < 0)
			change_y -= MINI_PLAYER_ICON_SIZE / (double)s->mini_height_unit;
		change_x = MINI_PLAYER_ICON_SIZE / (double)s->mini_width_unit;
		temp_change = -MINI_PLAYER_ICON_SIZE / (double)s->mini_width_unit;
	}
	temp_position.x = s->player_position.x + change_x;
	temp_position.y = s->player_position.y + change_y;
	temp_map_position.x = (int)temp_position.x;
	temp_map_position.y = (int)temp_position.y;
	if (s->map[temp_map_position.y][temp_map_position.x] == '1')
		return (true);
	if (change_x != 0)
	{
		temp_position.x = s->player_position.x + change_x;
		temp_position.y = s->player_position.y + temp_change;
	}
	else
	{
		temp_position.y = s->player_position.y + change_y;
		temp_position.x = s->player_position.x + temp_change;
	}
	temp_map_position.x = (int)temp_position.x;
	temp_map_position.y = (int)temp_position.y;
	if (s->map[temp_map_position.y][temp_map_position.x] == '1')
		return (true);
	return (false);
}

void	movement(double move_amount, double change_angle, t_main *s)
{
	// if (check_collision(change_x, change_y, s))
	// 	return ;
	s->player_position.x += move_amount * cos(s->player_angle + change_angle);
	s->player_position.y += move_amount * sin(s->player_angle + change_angle);
	s->player_map_position.x = (int)s->player_position.x;
	s->player_map_position.y = (int)s->player_position.y;
	redraw_window(s);
}

void	rotate(double change_angle, t_main *s)
{
	rotate_coor(&s->camera_plane.x, &s->camera_plane.y, change_angle);
	// rotate_coor(&s->player_direction.x, &s->player_direction.y, change_angle);
	s->player_angle += change_angle;
	redraw_window(s);
}

int	key_hooks(int keycode, t_main *s)
{
	(void)s;
	printf("hi 1\n");
	if (keycode == W_KEY)
		movement(MOVEMENT_AMOUNT, 0,s);
	else if (keycode == S_KEY)
		movement(MOVEMENT_AMOUNT, M_PI, s);
	else if (keycode == A_KEY)
		movement(MOVEMENT_AMOUNT, -M_PI_2, s);
	else if (keycode == D_KEY)
		movement(MOVEMENT_AMOUNT, M_PI_2, s);
	else if (keycode == LEFT_KEY)
		rotate(ROTATION_AMOUNT, s);
	else if (keycode == RIGHT_KEY)
		rotate(-ROTATION_AMOUNT, s);
	else if (keycode == M_KEY)
	{
		s->minimap_on = !s->minimap_on;
		redraw_window(s);
	}
	else if (keycode == ESC_KEY)
		close_x(0, s);
	// printf("%lf \n", s->player_angle); 	
	return (1);
}

int	close_x(int keycode, t_main *s)
{
	(void)keycode;
	(void)s;
	mlx_destroy_image(s->mlx, s->mlx_image);
	mlx_destroy_window(s->mlx, s->mlx_window);
	//free allocations
	exit(1);
}