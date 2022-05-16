/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:58:57 by ann               #+#    #+#             */
/*   Updated: 2022/05/16 13:00:40 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse(int argc, char **argv, t_pars *p)
{
	ft_bzero(p, sizeof(t_pars));
	user_input_check(argc, argv);
	init_map_save(argv[1], p);
	check_file_validity(p);
	p->map = &p->full_file[p->map_starting_i];
	check_map_content(p);
	if (p->map_error)
	{
		printf("%soooi .. fix your shit%s\n", RED, RESET);
		// printf("%sError: check map%s\n", RED, RESET);
		free_char_double_pointer(p->full_file);
		exit(0);
	}
}

static void	initiate_main_struct(t_main *s, t_pars *p)
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
	/* taking things from parser to main struct */
	s->map = p->map;
	s->map_height = p->map_h;
	s->map_width_max = p->map_w;
	s->ceiling_color = rgb_to_uint(0, p->c_color_rgb_int[0], p->c_color_rgb_int[1], p->c_color_rgb_int[2]);
	s->floor_color = rgb_to_uint(0, p->f_color_rgb_int[0], p->f_color_rgb_int[1], p->f_color_rgb_int[2]);

	assign_rgb_color(171, 174, 176, &s->fog);
	// uint_to_rgb(0xabaeb0, &s->fog);
	load_textures(p, s);
	printf("heieheihie\n");
}

/* to do:
	- change the player icon size to scale with the map
	- change the players movement to change with the map too */

int main(int argc, char **argv)
{
	t_main	s;
	t_pars	p;

	/* parse map */
	parse(argc, argv, &p);

	/* initiate struct */
	initiate_main_struct(&s, &p);

	/* initiate player info after parsing */
	initiate_player_info(&s);

	/* draw whatever is in the window */
	redraw_window(&s);

	/* hooks and loop */
	// mlx_key_hook(s.mlx_window, key_hooks, &s);
	mlx_hook(s.mlx_window, 2, 0, key_hooks, &s);
	mlx_hook(s.mlx_window, 6, 0, mouse_perspective, &s);
	mlx_hook(s.mlx_window, 17, 0, close_x, &s);
	mlx_loop(s.mlx);
}
