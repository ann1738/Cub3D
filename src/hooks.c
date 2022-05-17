/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 02:29:56 by ann               #+#    #+#             */
/*   Updated: 2022/05/17 17:20:34 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*still trial (make static)*/

#define NO_COLLISION 0
#define COLLISION_XY 1
#define COLLISION_X 2
#define COLLISION_Y 3

int	check_collision(double move_amount, double change_angle, t_main *s)
{
	double		offset;
	t_vector	temp_pos;

	offset = 0.5;

	temp_pos.x = s->player_position.x;
	temp_pos.y = s->player_position.y;
	temp_pos.x += (move_amount + offset) * cos(s->player_angle + change_angle);
	temp_pos.y += (move_amount + offset) * sin(s->player_angle + change_angle);
	// printf("player.x = %lf, playe /r.y = %lf --- x = %lf, y = %lf\n", s->player_position.x, s->player_position.y, temp_pos.x, temp_pos.y);
	if (s->map[(int)temp_pos.y][(int)temp_pos.x] == '1')
		return (COLLISION_XY);
	else if (s->map[(int)temp_pos.y][(int)s->player_position.x] == '1')
		return (COLLISION_Y);
	if (s->map[(int)s->player_position.y][(int)temp_pos.x] == '1')
		return (COLLISION_X);
	return (NO_COLLISION);
}

void	movement(double move_amount, double change_angle, t_main *s)
{
	t_vector	save;
	int			collision;
	
	collision = check_collision(move_amount, change_angle, s);
	if (collision == COLLISION_XY)
		{write(2, "COLLISION\n", 10); return ;}

	save.x = s->player_position.x;
	save.y = s->player_position.y;
	if(collision != COLLISION_X)
		s->player_position.x += move_amount * cos(s->player_angle + change_angle);
	if(collision != COLLISION_Y)
		s->player_position.y += move_amount * sin(s->player_angle + change_angle);
	//updating map/grid positions
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
	/* Making the player's angle wrap around (2 * PI) */
	if (s->player_angle > 2 * M_PI)
		s->player_angle = s->player_angle - (2 * M_PI);
	else if (s->player_angle < 0)
		s->player_angle = s->player_angle + (2 * M_PI);
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
	else if (keycode == H_KEY)
	{
		s->is_using_mouse = !s->is_using_mouse;
		if (s->is_using_mouse)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
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

int	mouse_perspective(int x, int y, t_main *s)
{
	(void)y;
	double	change_angle;

	// change_angle = (x - (WINDOW_X / 2)) / 534.760609;
		// change_angle = (x - (WINDOW_X / 2)) / 2139.042435;
	if (s->is_using_mouse)
	{
		change_angle = (x - (WINDOW_X / 2)) / 1069.521218;
		rotate(change_angle, s);
		mlx_mouse_move(s->mlx_window, WINDOW_X / 2, WINDOW_Y / 2);
	}
	return 1;
}
