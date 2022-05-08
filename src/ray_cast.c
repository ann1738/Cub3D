/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/08 23:07:31 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	d_abs(double x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	cast_rays(t_main *s)
{
	t_coord	temp_start;
	t_coord	temp_end;
	//calculate camera_x and ray direction *
	// for(int i = s->player_angle; i < 4; ++i){
	s->ray_direction.x = s->player_direction.x + s->camera_plane.x;
	s->ray_direction.y = s->player_direction.y + s->camera_plane.y;
	printf("hiihiihihihihhiihih%lf, %lf\n", s->ray_direction.x, s->ray_direction.y);
	//calculate delta distances *
	if (s->ray_direction.x != 0)
		s->delta_distance_x = sqrt(1 + (s->ray_direction.y / s->ray_direction.x) * (s->ray_direction.y / s->ray_direction.x));
	else
		s->delta_distance_x = 1e8;
	if (s->ray_direction.y != 0)
		s->delta_distance_y = sqrt(1 + (s->ray_direction.x / s->ray_direction.y) * (s->ray_direction.x / s->ray_direction.y));
	else
		s->delta_distance_y = 1e8;
	// calculating the inital ray length to reach the side of the next wall in terms of x and y
	if (s->ray_direction.x >= 0)
	{
		s->step.x = 1;
		s->side_length_x = ((s->player_map_position.x + 1) - s->player_position.x) * s->delta_distance_x;
	}
	else
	{
		s->step.x = -1;
		s->side_length_x = (s->player_position.x - s->player_map_position.x) * s->delta_distance_x;
	}
	s->player_map_position.x += s->step.x;
	if (s->ray_direction.y >= 0)
	{
		s->step.y = 1;
		s->side_length_y = ((s->player_map_position.y + 1) - s->player_position.y) * s->delta_distance_y;
	}
	else
	{
		s->step.y = -1;
		s->side_length_y = (s->player_position.y - s->player_map_position.y) * s->delta_distance_y;
	}
	s->player_map_position.y += s->step.y;

	// printf("ray_direction.x %lf .. ray_direction.y %lf\n", s->ray_direction.x, s->ray_direction.y);
	// printf("delta_distance.x %lf .. delta_distance.y %lf\n", s->delta_distance.x, s->delta_distance.y);
	// printf("side_distance.x %lf .. side_distance.y %lf\n", s->side_distance.x, s->side_distance.y);
	
	while (s->map[s->player_map_position.y][s->player_map_position.x] != '1')
	{
		printf("heyey\n");
		if (s->side_length_x < s->side_length_y)
		{
			s->side_length_x += s->delta_distance_x;
			s->final_side_length = s->side_length_x;
			s->player_map_position.x += s->step.x;
		}
		else
		{
			s->side_length_y += s->delta_distance_y;
			s->final_side_length = s->side_length_y;
			s->player_map_position.y += s->step.y;
		}
	}
	//start point
	temp_start.x = s->player_position.x * s->mini_width_unit; 
	temp_start.y = s->player_position.y * s->mini_height_unit; 
	//end point
	temp_end.x = temp_start.x + (s->final_side_length * s->mini_width_unit * cos(atan2(s->ray_direction.y, s->ray_direction.x)));
	temp_end.y = temp_start.y + (s->final_side_length * s->mini_height_unit * sin(atan2(s->ray_direction.y, s->ray_direction.x)));
	printf("start(%d, %d), end(%d, %d)\n", temp_start.x, temp_start.y, temp_end.x, temp_end.y);
	draw_line(temp_start, temp_end, s);
	// }
}

/* ************************************************************************** */
/* The goal is to cast a ray until hits a wall and use the distance to draw a */
/* vertical strip of the wall.                                                */
/* -------------------------------------------------------------------------- */
/* To do that:                                                                */
/* 1. calculate the length of the ray to traverse one x unit and also one y   */
/* unit. We'll call them s->delta_distance_x and s->delta_distance_y.         */
/* 2. calculate the inital hit to the next side wall in terms of hitting an x */
/* side or a y side.                                                          */
/* 3. use that */
/* ************************************************************************** */
