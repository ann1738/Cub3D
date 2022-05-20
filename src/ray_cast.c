/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/20 19:00:23 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_ray_dir_n_delta_dist(t_main *s, double i)
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

static void	calc_inital_side_len(t_main *s)
{
	s->step.x = 0;
	s->step.y = 0;
	/* calculating the inital ray length to reach the side of the next wall in terms of x and y */
	if (s->ray_direction.x >= 0 && (++s->step.x) >= 0)
		s->side_length_x = ((s->ray_map_position.x + 1) - s->player_position.x) * s->delta_distance_x;
	else if ((--s->step.x) <= 0)
		s->side_length_x = (s->player_position.x - s->ray_map_position.x) * s->delta_distance_x;
	if (s->ray_direction.y >= 0 && ((++s->step.y) >= 0))
		s->side_length_y = ((s->ray_map_position.y + 1) - s->player_position.y) * s->delta_distance_y;
	else if ((--s->step.y) <= 0)
		s->side_length_y = (s->player_position.y - s->ray_map_position.y) * s->delta_distance_y;
	if (s->side_length_x < s->side_length_y)
		s->final_side_length = s->side_length_x;
	else
		s->final_side_length = s->side_length_y;
	// printf("step_x = %d, step_y = %d\n", s->step.x, s->step.y);
}

int	assign(unsigned int *assigned, unsigned int assignee)
{
	*assigned = assignee;
	return (0);
}

static void	draw_wall(t_main *s)
{
	t_coord	origin;
	int		texture_index;

	texture_index = 0;
	/* which texture */
	if (s->ray_direction.x > 0 && s->side_hit == SIDE_X) //EAST
		texture_index = 3;
	else if (s->ray_direction.x < 0 && s->side_hit == SIDE_X) //WEST	
		texture_index = 2;
	else if (s->ray_direction.y > 0 && s->side_hit == SIDE_Y) //SOUTH
		texture_index = 1;
	else if (s->ray_direction.y < 0 && s->side_hit == SIDE_Y) //NORTH
		texture_index = 0;

	/* perpendicular distance instead of euclidean distance to avoid fish eye effect */
	s->perpend_wall_dist = s->final_side_length * fabs(cos(fabs(s->player_angle - atan2(s->ray_direction.y, s->ray_direction.x))));
	// if (s->perpend_wall_dist > s->depth)
	// 	return ;
	
	/* !!! seg fault is here !!! */
	/* !!! seg fault is here !!! */
	for (int i = 0; i < s->wall_width; i++)
		s->sprite->z_buffer[s->place_wall_at_x + i] = s->perpend_wall_dist;
	/* !!! seg fault is here !!! */
	/* !!! seg fault is here !!! */
		
	/* fixing near wall disturbances */
	if (s->perpend_wall_dist != 0) //not sure if necessary
		s->wall_height = WALL_SCALE_FACTOR * WINDOW_Y / s->perpend_wall_dist;
	else
		s->wall_height = WINDOW_Y;
	s->step_texture = s->texture[texture_index].height / (double)s->wall_height;
	s->texture_y = 0;
	if (s->wall_height + s->pitch > WINDOW_Y)
	{
		s->texture_y = ((s->wall_height - WINDOW_Y) / 2.0) * s->step_texture;
		s->wall_height = WINDOW_Y;
	}
	/**/	
	
	/* calculating the texture x coordinate*/
	if (s->side_hit == SIDE_X)
		s->wall_hit_pos = s->player_position.y + s->perpend_wall_dist * s->ray_direction.y;
	else
		s->wall_hit_pos = s->player_position.x + s->perpend_wall_dist * s->ray_direction.x;
	s->wall_hit_pos = s->wall_hit_pos - floor(s->wall_hit_pos);//to get the fraction

	s->offset = (int)(s->wall_hit_pos * s->texture[texture_index].width);

	s->texture_x = s->offset;
	//understand the math here please
	if (s->side_hit == SIDE_X && s->ray_direction.x > 0)
		s->texture_x = s->texture[texture_index].width - s->texture_x - 1;
	else if (s->side_hit == SIDE_Y && s->ray_direction.y < 0)
		s->texture_x = s->texture[texture_index].width - s->texture_x - 1;
	/* calculating the step_texture used in the drawing part */

	// s->wall_height = (ACTUAL_WALL_HEIGHT / s->perpend_wall_dist) * s->dist_to_projection_plane;

	/* shading using fog */	
	s->fog_intensity = 0; //reset fog_intensity (useless but it looks better with it, for now)
	if (s->perpend_wall_dist <= s->depth / 2.0)
		s->fog_intensity = 0;
	else if (s->perpend_wall_dist <= s->depth / 1.9)
		s->fog_intensity = 0.1;
	else if (s->perpend_wall_dist <= s->depth / 1.8)
		s->fog_intensity = 0.2;
	else if (s->perpend_wall_dist <= s->depth / 1.7)
		s->fog_intensity = 0.3;
	else if (s->perpend_wall_dist <= s->depth / 1.6)
		s->fog_intensity = 0.4;
	else if (s->perpend_wall_dist <= s->depth / 1.5)
		s->fog_intensity = 0.5;
	else if (s->perpend_wall_dist <= s->depth / 1.4)
		s->fog_intensity = 0.6;
	else if (s->perpend_wall_dist <= s->depth / 1.3)
		s->fog_intensity = 0.7;
	else if (s->perpend_wall_dist <= s->depth / 1.2)
		s->fog_intensity = 0.8;
	else if (s->perpend_wall_dist <= s->depth / 1.1)
		s->fog_intensity = 0.9;
	else if (s->perpend_wall_dist <= s->depth / 1.0)
		s->fog_intensity = 1;
	else if (s->perpend_wall_dist > s->depth)
		s->fog_intensity = 1;
		// return ;
	origin.x = s->place_wall_at_x;
	//start of where to draw
	origin.y = (WINDOW_Y / 2.0) - (s->wall_height / 2.0) + s->pitch + (s->position_z / s->perpend_wall_dist);
	//origin color is not used here (in the draw_vertical_texture())
	// origin.color = HX_PURPLE;
	draw_vertical_texture(origin, s->wall_width, s->wall_height, &s->texture[texture_index], s);
}

static void	ray_casting_loop(t_main *s)
{
	while (s->final_side_length <= s->depth && s->map[s->ray_map_position.y][s->ray_map_position.x] != '1')
	{
		// printf("I AM IN side.x = %lf , side.y = %lf\n", s->side_length_x, s->side_length_y);
		if (s->side_length_x < s->side_length_y)
		{
			s->final_side_length = s->side_length_x;
			s->side_length_x += s->delta_distance_x;
			s->ray_map_position.x += s->step.x;
			s->side_hit = SIDE_X;
		}
		else
		{
			s->final_side_length = s->side_length_y;
			s->side_length_y += s->delta_distance_y;
			s->ray_map_position.y += s->step.y;
			s->side_hit = SIDE_Y;
		}
		// printf("HULU!!!!\nfinal_side_length = %lf -- ", s->final_side_length);

		/* protection for when there is no wall / wall is too far */
		if (s->ray_map_position.y > s->map_height - 1 || s->ray_map_position.x > s->map_width_max - 1) //protect negative
		{
			s->final_side_length = s->depth;
			break ;
		}
		// printf("I AM IN (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);

		/* sprite count */
		if (s->map[s->ray_map_position.y][s->ray_map_position.x] == 'L' && !check_if_coord_exist(s, s->ray_map_position.x, s->ray_map_position.y))
		{
			printf("%shiii %d%s\n", GREEN1, s->sprite->in_screen_count, RESET);
			s->sprite->position[s->sprite->in_screen_count].x = s->ray_map_position.x;
			s->sprite->position[s->sprite->in_screen_count].y = s->ray_map_position.y;
			s->sprite->in_screen_count += 1;
			printf("%shiii %d%s\n", BLUE1, s->sprite->in_screen_count, RESET);
		}
	}
	if (s->final_side_length > s->depth)
		s->dont_draw = true;
		
}

void	cast_rays(t_main *s)
{
	double i;
	t_coord temp_start, temp_end;

	/* calculating fps */
	// fps(s);
	s->dont_draw = false;
	i = 1;
	s->place_wall_at_x = 0;
	s->wall_width = WINDOW_X / (2.0 / INCREMENT_RAY_CASTING) + 1;
	//WINDOW_X divided by the number of rays casted (plus one bec the condition of the loop is >= not >.. actually idk why?!)
	while (i >= -1)
	{
		/* calculations before the main ray casting loop */
		calc_ray_dir_n_delta_dist(s, i);
		calc_inital_side_len(s);
		// printf("START RAY (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);

		/* main ray casting loop */
		ray_casting_loop(s);

		// printf("ray end(%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
	

		if (s->minimap_on)
		{
			//start point
			temp_start.x = MINIMAP_X / 2 + MINI_OFFSET_X; 
			temp_start.y = MINIMAP_Y / 2 + MINI_OFFSET_Y; 
			//end point
			temp_end.x = temp_start.x + (s->final_side_length * MINI_BLOCK_SIZE_X * cos(atan2(s->ray_direction.y, s->ray_direction.x)));
			temp_end.y = temp_start.y + (s->final_side_length * MINI_BLOCK_SIZE_Y * sin(atan2(s->ray_direction.y, s->ray_direction.x)));
	
			// if (temp_end.x >= MINIMAP_X + MINI_OFFSET_X)
			// 	temp_end.x = MINIMAP_X + MINI_OFFSET_X - 1;
			// else if (temp_end.x <= MINI_OFFSET_X)
			// 	temp_end.x = MINI_OFFSET_X + 1;
		
			// if (temp_end.y >= MINIMAP_Y + MINI_OFFSET_Y)
			// 	temp_end.y = MINIMAP_Y + MINI_OFFSET_Y - 1;
			// else if (temp_end.y <= MINI_OFFSET_Y)
			// 	temp_end.y = MINI_OFFSET_Y + 1;
			
			draw_line(temp_start, temp_end, s);
		}
		/*drawing the wall*/
		// if (s->dont_draw == false)
			draw_wall(s);

		/* incrementing loop */
		i -= INCREMENT_RAY_CASTING;
		s->place_wall_at_x += s->wall_width;
	}

}

/* code for drawing lines to represent the rays casted */
		
/*******************************************************/

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
