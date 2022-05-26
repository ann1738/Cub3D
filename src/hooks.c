/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 02:29:56 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 18:38:27 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	restore_position(t_vector *save, t_main *s)
{
	s->player_position.x = save->x;
	s->player_position.y = save->y;
	s->player_map_position.x = (int)save->x;
	s->player_map_position.y = (int)save->y;
	return ;
}

/* function to manage the player's movement */
void	movement(double move_amount, double change_angle, t_main *s)
{
	t_vector	save;
	int			collision;

	collision = check_collision(move_amount, change_angle, s);
	if (collision == COLLISION_XY)
		return ;
	save.x = s->player_position.x;
	save.y = s->player_position.y;
	if (collision != COLLISION_X)
		s->player_position.x += move_amount * \
		cos(s->player_angle + change_angle);
	if (collision != COLLISION_Y)
		s->player_position.y += move_amount * \
		sin(s->player_angle + change_angle);
	s->player_map_position.x = (int)s->player_position.x;
	s->player_map_position.y = (int)s->player_position.y;
	if (s->map[s->player_map_position.y][s->player_map_position.x] == '1' \
	|| s->map[s->player_map_position.y][s->player_map_position.x] == ' ')
		return (restore_position(&save, s));
	if (s->map[s->player_map_position.y][s->player_map_position.x] == 'L')
	{
		s->map[s->player_map_position.y][s->player_map_position.x] = '0';
		s->p->full_sprite_count--;
	}
	redraw_window(s);
}

/* function to manage the player's rotation */
void	rotate(double change_angle, t_main *s)
{
	rotate_coor(&s->camera_plane.x, &s->camera_plane.y, change_angle);
	s->player_angle += change_angle;
	if (s->player_angle > 2 * M_PI)
		s->player_angle = s->player_angle - (2 * M_PI);
	else if (s->player_angle < 0)
		s->player_angle = s->player_angle + (2 * M_PI);
	redraw_window(s);
}

/* function to manage the player's rotation */
int	key_hooks(int keycode, t_main *s)
{
	if (!s->start_screen_done && keycode != ESC_KEY)
		toggle_start_n_draw(s);
	else if (keycode == ESC_KEY)
		close_x(s);
	else if (keycode == H_KEY)
		toggle_mouse(s);
	else if (s->end_screen_done)
		return (0);
	else if (keycode == W_KEY)
		movement(MOVEMENT_AMOUNT, 0, s);
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
		toggle_minimap_n_draw(s);
	else if (keycode == I_KEY)
		toggle_info_n_draw(s);
	return (0);
}

/* function to deal with mouse rotation when the mouse feature is on */
int	mouse_perspective(int x, int y, t_main *s)
{
	double	change_angle;

	(void)y;
	if (!s->end_screen_done && s->is_using_mouse)
	{
		change_angle = (x - (WINDOW_X / 2)) / 1069.521218;
		rotate(change_angle, s);
		mlx_mouse_move(s->mlx_window, WINDOW_X / 2, WINDOW_Y / 2);
	}
	return (0);
}
