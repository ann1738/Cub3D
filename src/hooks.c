/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 02:29:56 by ann               #+#    #+#             */
/*   Updated: 2022/05/15 19:23:22 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*still trial (make static)*/

bool	check_collision(double move_amount, double change_angle, t_main *s)
{
	double		offset;
	t_vector	temp_pos;

	offset = 0.5;

	temp_pos.x = s->player_position.x;
	temp_pos.y = s->player_position.y;
	temp_pos.x += (move_amount + offset) * cos(s->player_angle + change_angle);
	temp_pos.y += (move_amount + offset) * sin(s->player_angle + change_angle);
	printf("player.x = %lf, player.y = %lf --- x = %lf, y = %lf\n", s->player_position.x, s->player_position.y, temp_pos.x, temp_pos.y);
	if (s->map[(int)temp_pos.y][(int)temp_pos.x] == '1')
		return (true);
	return (false);
}

void	movement(double move_amount, double change_angle, t_main *s)
{
	if (check_collision(move_amount, change_angle, s))
		{write(2, "COLLISION\n", 10); return ;}
	t_vector	save;

	save.x = s->player_position.x;
	save.y = s->player_position.y;
	s->player_position.x += move_amount * cos(s->player_angle + change_angle);
	s->player_position.y += move_amount * sin(s->player_angle + change_angle);
	s->player_map_position.x = (int)s->player_position.x;
	s->player_map_position.y = (int)s->player_position.y;
	/* i am still trying to make this work */
	// printf("player's angle is <%lf> ---- changed angle is <%lf>\n", s->player_angle, s->player_angle + change_angle);
	// printf("map placeholder is <%c>\n", s->map[s->player_map_position.y][s->player_map_position.x]);
	if (s->map[s->player_map_position.y][s->player_map_position.x] == '1' || s->map[s->player_map_position.y][s->player_map_position.x] == ' ')
	{
		s->player_position.x = save.x;
		s->player_position.y = save.y;
		s->player_map_position.x = (int)save.x;
		s->player_map_position.y = (int)save.y;
		return ;
	}
	redraw_window(s);
}

void	rotate(double change_angle, t_main *s)
{
	rotate_coor(&s->camera_plane.x, &s->camera_plane.y, change_angle);
	s->player_angle += change_angle;
	redraw_window(s);
}

int	key_hooks(int keycode, t_main *s)
{
	(void)s;
	if (keycode == W_KEY)
		movement(MOVEMENT_AMOUNT, 0,s);
	else if (keycode == S_KEY)
		movement(MOVEMENT_AMOUNT, M_PI, s);
	else if (keycode == A_KEY)
		movement(MOVEMENT_AMOUNT, M_PI + M_PI_2, s);
	else if (keycode == D_KEY)
		movement(MOVEMENT_AMOUNT, M_PI_2, s);
	else if (keycode == LEFT_KEY)
		rotate(-ROTATION_AMOUNT, s);
	else if (keycode == RIGHT_KEY)
		rotate(ROTATION_AMOUNT, s);
	else if (keycode == M_KEY)
	{
		s->minimap_on = !s->minimap_on;
		redraw_window(s);
	}
	else if (keycode == ESC_KEY)
		close_x(0, s);
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
