/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 02:29:56 by ann               #+#    #+#             */
/*   Updated: 2022/05/17 13:22:15 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*this works for the most part (there is some ways to surpass it)*/

#define NO_COLLISION 0
#define COLLISION_XY 1
#define COLLISION_X 2
#define COLLISION_Y 3

int	check_collision(double move_amount, double change_angle, t_main *s)
{
	// double		offset;
	t_vector	temp_pos;
	t_vector	player_direction;
	bool	collision_x = false;
	bool	collision_y = false;
	// offset = WALL_COLLISION_OFFSET;

	temp_pos.x = s->player_position.x;
	temp_pos.y = s->player_position.y;
	temp_pos.x += (move_amount) * cos(s->player_angle + change_angle);
	temp_pos.y += (move_amount) * sin(s->player_angle + change_angle);
	player_direction.x = cos(s->player_angle + change_angle);
	player_direction.y = sin(s->player_angle + change_angle);

	t_vector	step;
	step.x = (temp_pos.x - s->player_position.x) / 10.0;
	step.y = (temp_pos.y - s->player_position.y) / 10.0;
	temp_pos.x = s->player_position.x;
	temp_pos.y = s->player_position.y;
	
	// this has potential to replace the if conditions
	int	x_abs;
	int	y_abs;
	if (player_direction.x != 0)
		x_abs = player_direction.x / fabs(player_direction.x);
	else
		x_abs = 0;
	if (player_direction.y != 0)
		y_abs = player_direction.y / fabs(player_direction.y);
	else
		y_abs = 0;
	int i = 0;
	while (i < 10)
	{
		if (!collision_x && player_direction.x > 0) //right
		{
			if (s->map[(int)s->player_position.y][(int)s->player_position.x + 1] == '1' && ceil(s->player_position.x) - temp_pos.x <= WALL_COLLISION_OFFSET) //wall right
				collision_x = true;
		}
		else if (!collision_x && player_direction.x < 0) //left
		{
			if (s->map[(int)s->player_position.y][(int)s->player_position.x - 1] == '1' && temp_pos.x - floor(s->player_position.x) <= WALL_COLLISION_OFFSET) //wall left
				collision_x = true;
		}
		if (!collision_y && player_direction.y > 0) //down
		{
			if (s->map[(int)s->player_position.y + 1][(int)s->player_position.x] == '1' && ceil(s->player_position.y) - temp_pos.y <= WALL_COLLISION_OFFSET) //wall below
				collision_y = true;
		}
		else if (!collision_y && player_direction.y < 0) //up
		{
			if (s->map[(int)s->player_position.y - 1][(int)s->player_position.x] == '1' && temp_pos.y - floor(s->player_position.y) <= WALL_COLLISION_OFFSET) //wall above
				collision_y = true;
		}
		if ((!collision_x || !collision_y) && s->map[(int)(s->player_position.y + y_abs)][(int)(s->player_position.x + x_abs)] == '1' && s->map[(int)(s->player_position.y + y_abs)][(int)(s->player_position.x)] != '1' && s->map[(int)(s->player_position.y)][(int)(s->player_position.x + x_abs)] != '1')
		{
			if ((((player_direction.y > 0 && ceil(s->player_position.y) - temp_pos.y <= WALL_COLLISION_OFFSET - 0.1 )|| (player_direction.y < 0 && temp_pos.y - floor(s->player_position.y) <= WALL_COLLISION_OFFSET - 0.1)))
			&& ((player_direction.x > 0 && ceil(s->player_position.x) - temp_pos.x <= WALL_COLLISION_OFFSET - 0.1) || (player_direction.x < 0 && temp_pos.x - floor(s->player_position.x) <= WALL_COLLISION_OFFSET - 0.1))) 
			{	
				collision_y = true;
				collision_x = true;
				printf("hey iam here\n");
			}
		}
		temp_pos.x += step.x;
		temp_pos.y += step.y;
		i++;
	}
	if (collision_x && collision_y)
		return (COLLISION_XY);
	else if (collision_x)
		return (COLLISION_X);
	else if (collision_y)
		return (COLLISION_Y);
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
