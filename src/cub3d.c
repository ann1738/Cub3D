/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:58:57 by ann               #+#    #+#             */
/*   Updated: 2022/05/10 16:44:50 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_struct(t_main *s)
{	
	ft_bzero(s, sizeof(t_main));
	s->mlx = mlx_init();
	s->mlx_window = mlx_new_window(s->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	s->mlx_image = mlx_new_image(s->mlx, WINDOW_X, WINDOW_Y);
	s->image_address = mlx_get_data_addr(s->mlx_image, &s->bpp, &s->size_line, &s->endian);
}

void	temp_parse(char *path, t_main *s)
{
	s->map_height = get_y(path);
	s->map = save_map(s->map, path, s->map_height);
	int i = -1;
	while (s->map[0][++i] && s->map[0][i] != '\n')
		s->map_width++;
}

//to do
//change the player icon size to scale with the map
//change the players movement to change with the map too 

int main(int argc, char **argv)
{
	t_main	s;

	if (argc != 2)
		return (write(2, "Invalid\n", 8));
	//initiate struct
	init_struct(&s);
	//parse map
	temp_parse(argv[1], &s);
	//initiate player info after parsing
	initiate_player_info(&s);
	// if (s.map_width >= MINIMAP_X || s.map_height >= MINIMAP_Y) //if map is too big
	// 	exit(write(STDERR_FILENO, "Error: Map is too big to be rendered\n", 37));
	s.mini_width_unit = round((double)MINIMAP_X / s.map_width);
	s.mini_height_unit = round((double)MINIMAP_Y / s.map_height);
	//draw floor and ceiling
	draw_floor(FLOOR_COLOR, &s);
	draw_ceiling(CEILING_COLOR, &s);
	//draw map
	// draw_minimap(&s);
	//cast rays
	cast_rays(&s);
	// s.player_map_position.x = (int)s.player_position.x;
	// s.player_map_position.y = (int)s.player_position.y;
	mlx_put_image_to_window(s.mlx, s.mlx_window, s.mlx_image, 0, 0);
	mlx_hook(s.mlx_window, 2, 0, key_hooks, &s);
	mlx_hook(s.mlx_window, 17, 0, close_x, &s);
	mlx_loop(s.mlx);
}