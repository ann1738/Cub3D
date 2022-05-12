/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:58:57 by ann               #+#    #+#             */
/*   Updated: 2022/05/12 17:55:08 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_struct(t_main *s)
{	
	ft_bzero(s, sizeof(t_main));

	/* mlx initialization */
	s->mlx = mlx_init();
	s->mlx_window = mlx_new_window(s->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	s->mlx_image = mlx_new_image(s->mlx, WINDOW_X, WINDOW_Y);
	s->image_address = mlx_get_data_addr(s->mlx_image, &s->bpp, &s->size_line, &s->endian);

	/* other initialization */
	s->depth = VISION_DEPTH;
	s->frame1 = clock();
	// s->dist_to_projection_plane = (WINDOW_X / 2) / tan(deg_to_rad(FOV_DEG / 2));
}

void	temp_parse(char *path, t_main *s)
{
	s->map_height = get_y(path);
	s->map = save_map(s->map, path, s->map_height);
	int i = -1;
	while (s->map[0][++i] && s->map[0][i] != '\n')
		s->map_width++;
}

/* to do:
	- change the player icon size to scale with the map
	- change the players movement to change with the map too */

int main(int argc, char **argv)
{
	t_main	s;

	if (argc != 2)
		return (write(2, "Invalid\n", 8));

	/* initiate struct */
	init_struct(&s);

	/* parse map */
	temp_parse(argv[1], &s);

	/* initiate player info after parsing */
	initiate_player_info(&s);

	/* draw whatever is in the window */
	redraw_window(&s);

	/* hooks and loop */
	mlx_hook(s.mlx_window, 2, 0, key_hooks, &s);
	mlx_hook(s.mlx_window, 17, 0, close_x, &s);
	mlx_loop(s.mlx);
}
