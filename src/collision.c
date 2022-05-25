/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:18:31 by ann               #+#    #+#             */
/*   Updated: 2022/05/25 12:52:20 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	init_collision_struct(double move_amount, double change_angle, \
// t_collision *c, t_main *s)
// {
// 	c->temp_pos.x = s->player_position.x;
// 	c->temp_pos.y = s->player_position.y;
// 	c->temp_pos.x += (move_amount) * cos(s->player_angle + change_angle);
// 	c->temp_pos.y += (move_amount) * sin(s->player_angle + change_angle);
// 	c->player_direction.x = cos(s->player_angle + change_angle);
// 	c->player_direction.y = sin(s->player_angle + change_angle);

// 	c->step.x = (c->temp_pos.x - s->player_position.x) / 10.0;
// 	c->step.y = (c->temp_pos.y - s->player_position.y) / 10.0;
// 	c->temp_pos.x = s->player_position.x;
// 	c->temp_pos.y = s->player_position.y;
	
// 	// this has potential to replace the if conditions
// 	c->abs.x = 0;
// 	c->abs.y = 0;
// 	if (c->player_direction.x != 0)
// 		c->abs.x = c->player_direction.x / fabs(c->player_direction.x);
// 	if (c->player_direction.y != 0)
// 		c->abs.y = c->player_direction.y / fabs(c->player_direction.y);
// }

// static void	check_side_walls(t_collision *c, t_main *s)
// {
// 	if (!c->collision_x && c->player_direction.x > 0) //right
// 	{
// 		if (s->map[(int)s->player_position.y][(int)s->player_position.x + 1] == '1' && ceil(s->player_position.x) - c->temp_pos.x <= WALL_COLLISION_OFFSET) //wall right
// 			c->collision_x = true;
// 	}
// 	else if (!c->collision_x && c->player_direction.x < 0) //left
// 	{
// 		if (s->map[(int)s->player_position.y][(int)s->player_position.x - 1] == '1' && c->temp_pos.x - floor(s->player_position.x) <= WALL_COLLISION_OFFSET) //wall left
// 			c->collision_x = true;
// 	}
// 	if (!c->collision_y && c->player_direction.y > 0) //down
// 	{
// 		if (s->map[(int)s->player_position.y + 1][(int)s->player_position.x] == '1' && ceil(s->player_position.y) - c->temp_pos.y <= WALL_COLLISION_OFFSET) //wall below
// 			c->collision_y = true;
// 	}
// 	else if (!c->collision_y && c->player_direction.y < 0) //up
// 	{
// 		if (s->map[(int)s->player_position.y - 1][(int)s->player_position.x] == '1' && c->temp_pos.y - floor(s->player_position.y) <= WALL_COLLISION_OFFSET) //wall above
// 			c->collision_y = true;
// 	}
// }

// static void	check_open_corner(t_collision *c, t_main *s)
// {
// 	if ((!c->collision_x || !c->collision_y) && s->map[(int)(s->player_position.y + c->abs.y)][(int)(s->player_position.x + c->abs.x)] == '1' && s->map[(int)(s->player_position.y + c->abs.y)][(int)(s->player_position.x)] != '1' && s->map[(int)(s->player_position.y)][(int)(s->player_position.x + c->abs.x)] != '1')
// 	{
// 		if ((((c->player_direction.y > 0 && ceil(s->player_position.y) - c->temp_pos.y <= WALL_COLLISION_OFFSET - 0.1 )|| (c->player_direction.y < 0 && c->temp_pos.y - floor(s->player_position.y) <= WALL_COLLISION_OFFSET - 0.1)))
// 		&& ((c->player_direction.x > 0 && ceil(s->player_position.x) - c->temp_pos.x <= WALL_COLLISION_OFFSET - 0.1) || (c->player_direction.x < 0 && c->temp_pos.x - floor(s->player_position.x) <= WALL_COLLISION_OFFSET - 0.1))) 
// 		{	
// 			c->collision_y = true;
// 			c->collision_x = true;
// 		}
// 	}
// }

// /*this works for the most part (there is some ways to surpass it)*/

// int	check_collision(double move_amount, double change_angle, t_main *s)
// {
// 	int			i;
// 	t_collision c;

// 	// c.temp_pos.x = s->player_position.x;
// 	// c.temp_pos.y = s->player_position.y;
// 	// c.temp_pos.x += (move_amount) * cos(s->player_angle + change_angle);
// 	// c.temp_pos.y += (move_amount) * sin(s->player_angle + change_angle);
// 	// c.player_direction.x = cos(s->player_angle + change_angle);
// 	// c.player_direction.y = sin(s->player_angle + change_angle);

// 	// c.step.x = (c.temp_pos.x - s->player_position.x) / 10.0;
// 	// c.step.y = (c.temp_pos.y - s->player_position.y) / 10.0;
// 	// c.temp_pos.x = s->player_position.x;
// 	// c.temp_pos.y = s->player_position.y;
	
// 	// // this has potential to replace the if conditions
// 	// c.abs.x = 0;
// 	// c.abs.y = 0;
// 	// if (c.player_direction.x != 0)
// 	// 	c.abs.x = c.player_direction.x / fabs(c.player_direction.x);
// 	// if (c.player_direction.y != 0)
// 	// 	c.abs.y = c.player_direction.y / fabs(c.player_direction.y);
// 	init_collision_struct(move_amount, change_angle, &c, s);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		check_side_walls(&c, s);
// 		check_open_corner(&c, s);
// 		c.temp_pos.x += c.step.x;
// 		c.temp_pos.y += c.step.y;
// 		i++;
// 	}
// 	if (c.collision_x && c.collision_y)
// 		return (COLLISION_XY);
// 	else if (c.collision_x)
// 		return (COLLISION_X);
// 	else if (c.collision_y)
// 		return (COLLISION_Y);
// 	return (NO_COLLISION);
// }
