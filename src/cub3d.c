/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:58:57 by ann               #+#    #+#             */
/*   Updated: 2022/05/25 18:43:18 by aalsuwai         ###   ########.fr       */
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

static void	initiate_main_struct(t_main *s, t_pars *p, t_sprite *sprite)
{
	ft_bzero(s, sizeof(t_main));
	ft_bzero(sprite, sizeof(t_sprite));

	/* mlx initialization */
	s->mlx = mlx_init();
	s->mlx_window = mlx_new_window(s->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	s->mlx_image = mlx_new_image(s->mlx, WINDOW_X, WINDOW_Y);
	s->image_address = mlx_get_data_addr(s->mlx_image, &s->bpp, &s->size_line, &s->endian);

	/* other initialization */
	s->depth = VISION_DEPTH;
	s->frame1 = clock();

	/* taking things from parser to main struct */
	s->p = p;
	s->map = p->map;
	s->map_height = p->map_h;
	s->map_width_max = p->map_w;
	s->ceiling_color = rgb_to_uint(0, p->c_color_rgb_int[0], p->c_color_rgb_int[1], p->c_color_rgb_int[2]);
	s->floor_color = rgb_to_uint(0, p->f_color_rgb_int[0], p->f_color_rgb_int[1], p->f_color_rgb_int[2]);

	/* defining useful colors */
	assign_rgb_color(171, 174, 176, &s->fog);
	assign_rgb_color(57,57,57, &s->minimap_color);
	assign_rgb_color(0, 0, 0, &s->black);
	load_textures(p, s);

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! MALLOC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	sprite->position = ft_calloc(s->p->full_sprite_count, sizeof(t_coord));
	s->sprite = sprite;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* features to start with the game or to be toggled by the player */
	s->minimap_on = MINIMAP_DEFAULT == 1;
	s->is_using_mouse = MOUSE_DEFAULT == 1 && !mlx_mouse_hide(); //hehe
	s->info_panel_on = INFO_DEFAULT == 1;
}

int main(int argc, char **argv)
{
	t_sprite	sprite;
	t_main		s;
	t_pars		p;

	// printf("** %d **\n", s.sprite->in_screen_count);

	/* parse map */
	parse(argc, argv, &p);

	/* initiate struct */
	initiate_main_struct(&s, &p, &sprite);

	/* initiate player info after parsing */
	initiate_player_info(&s);

	/* start screen */
	mlx_put_image_to_window(s.mlx, s.mlx_window, s.start_screen.image, 0, 0);

	/* hooks and loop */
	// mlx_key_hook(s.mlx_window, key_hooks, &s);
	mlx_hook(s.mlx_window, 2, 0, key_hooks, &s);
	mlx_hook(s.mlx_window, 6, 0, mouse_perspective, &s);
	mlx_hook(s.mlx_window, 17, 0, close_x, &s);
	mlx_loop_hook(s.mlx, animation, &s);
	mlx_loop(s.mlx);
}
