/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/09 17:57:03 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double	d_abs(double x)
// {
// 	if (x < 0)
// 		x *= -1;
// 	return (x);
// }

// s->ray_direction.x = s->player_direction.x + s->camera_plane.x;
// s->ray_direction.y = s->player_direction.y + s->camera_plane.y;

void	calc_ray_dir_n_delta_dist(t_main *s, double i)
{
	//calculate ray direction and initialize s->ray_map_position with the player map position
	s->ray_direction.x = cos(s->player_angle) + (s->camera_plane.x * i);
	s->ray_direction.y = sin(s->player_angle) + (s->camera_plane.y * i);
	s->ray_map_position.x = s->player_map_position.x;
	s->ray_map_position.y = s->player_map_position.y;
	//calculate delta distances *
	if (s->ray_direction.x != 0)
		s->delta_distance_x = sqrt(1 + (s->ray_direction.y / s->ray_direction.x) * (s->ray_direction.y / s->ray_direction.x));
	else
		s->delta_distance_x = 1e8;
	if (s->ray_direction.y != 0)
		s->delta_distance_y = sqrt(1 + (s->ray_direction.x / s->ray_direction.y) * (s->ray_direction.x / s->ray_direction.y));
	else
		s->delta_distance_y = 1e8;
}

void	calc_inital_side_len(t_main *s)
{
	// calculating the inital ray length to reach the side of the next wall in terms of x and y
	if (s->ray_direction.x >= 0)
	{
		s->step.x = 1;
		s->side_length_x = ((s->ray_map_position.x + 1) - s->player_position.x) * s->delta_distance_x;
	}
	else
	{
		s->step.x = -1;
		s->side_length_x = (s->player_position.x - s->ray_map_position.x) * s->delta_distance_x;
	}
	if (s->ray_direction.y >= 0)
	{
		s->step.y = 1;
		s->side_length_y = ((s->ray_map_position.y + 1) - s->player_position.y) * s->delta_distance_y;
	}
	else
	{
		s->step.y = -1;
		s->side_length_y = (s->player_position.y - s->ray_map_position.y) * s->delta_distance_y;
	}
	if (s->side_length_x < s->side_length_y)
		s->final_side_length = s->side_length_x;
	else
		s->final_side_length = s->side_length_y;
	printf("step_x = %d, step_y = %d\n", s->step.x, s->step.y);
}

void	cast_rays(t_main *s)
{
	t_coord	temp_start;
	t_coord	temp_end;
	double i;

	i = -1;
	while (i <= 1)
	{
		calc_ray_dir_n_delta_dist(s, i);
		calc_inital_side_len(s);
		printf("START RAY (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
		while (s->map[s->ray_map_position.y][s->ray_map_position.x] != '1')
		{
			printf("I AM IN side.x = %lf, side.y = %lf\n", s->side_length_x, s->side_length_y);
			if (s->side_length_x < s->side_length_y)
			{
				s->final_side_length = s->side_length_x;
				s->side_length_x += s->delta_distance_x;
				s->ray_map_position.x += s->step.x;
			}
			else
			{
				s->final_side_length = s->side_length_y;
				s->side_length_y += s->delta_distance_y;
				s->ray_map_position.y += s->step.y;
			}
			printf("I AM IN (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
		}
		printf("ray end(%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
		//start point
		temp_start.x = s->player_position.x * s->mini_width_unit; 
		temp_start.y = s->player_position.y * s->mini_height_unit; 
		//end point
		// printf("final ray length %lf\n", s->final_side_length);
		temp_end.x = temp_start.x + (s->final_side_length * s->mini_width_unit * cos(atan2(s->ray_direction.y, s->ray_direction.x)));
		temp_end.y = temp_start.y + (s->final_side_length * s->mini_height_unit * sin(atan2(s->ray_direction.y, s->ray_direction.x)));
		// printf("start(%d, %d), end(%d, %d)\n", temp_start.x, temp_start.y, temp_end.x, temp_end.y);
		draw_line(temp_start, temp_end, s);
		i += 0.1;
	}
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
