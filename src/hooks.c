/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 02:29:56 by ann               #+#    #+#             */
/*   Updated: 2022/05/07 21:02:38 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement(int change_x, int change_y, t_main *s)
{
	ft_bzero(s->image_address, WINDOW_X * WINDOW_Y);
	s->player_position.x += change_x;
	s->player_position.y += change_y;
	if (s->player_position.x > (s->player_map_position.x * s->mini_width_unit) + s->mini_width_unit)
		++s->player_map_position.x;
	else if(s->player_position.x < (s->player_map_position.x * s->mini_width_unit))
		--s->player_map_position.x;
	if (s->player_position.y > (s->player_map_position.y * s->mini_height_unit) + s->mini_height_unit)
		s->player_map_position.y++;
	else if(s->player_position.y < (s->player_map_position.y * s->mini_height_unit))
		--s->player_map_position.y;
	update_minimap(s);
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
}

void	rotate(double change_angle, t_main *s)
{
	ft_bzero(s->image_address, WINDOW_X * WINDOW_Y);
	rotate_coor(&s->camera_plane.x, &s->camera_plane.y, change_angle);
	rotate_coor(&s->player_direction.x, &s->player_direction.y, change_angle);
	update_minimap(s);
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);	
}

int	key_hooks(int keycode, t_main *s)
{
	(void)s;
	printf("%d\n", keycode);
	if (keycode == W_KEY)
		movement(0, -MOVEMENT_AMOUNT, s);
	else if (keycode == S_KEY)
		movement(0, MOVEMENT_AMOUNT, s);
	else if (keycode == A_KEY)
		movement(-MOVEMENT_AMOUNT, 0, s);
	else if (keycode == D_KEY)
		movement(MOVEMENT_AMOUNT, 0, s);
	else if (keycode == LEFT_KEY)
		rotate(-ROTATION_AMOUNT, s);
	else if (keycode == RIGHT_KEY)
		rotate(ROTATION_AMOUNT, s);
	else if (keycode == ESC_KEY)
		close_x(0, s);
	return (1);
}

int	close_x(int keycode, t_main *s)
{
	(void)keycode;
	(void)s;
	// mlx_destroy_image(s->mlx, s->mlx_image);
	// mlx_destroy_window(s->mlx, s->mlx_window);
	//free allocations
	exit(1);
}