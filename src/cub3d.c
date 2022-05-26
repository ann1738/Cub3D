/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:58:57 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 19:02:28 by anasr            ###   ########.fr       */
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
		printf("%sError: check map%s\n", RED, RESET);
		free_char_double_pointer(p->full_file);
		exit(1);
	}
}

static void	set_defult_setting(t_main *s)
{
	s->info_panel_on = INFO_DEFAULT == 1;
	s->minimap_on = MINIMAP_DEFAULT == 1;
	s->is_using_mouse = MOUSE_DEFAULT == 1;
	if (s->is_using_mouse)
		mlx_mouse_hide();
}

static void	initiate_main_struct(t_main *s, t_pars *p, t_sprite *sprite)
{
	ft_bzero(s, sizeof(t_main));
	ft_bzero(sprite, sizeof(t_sprite));
	s->mlx = mlx_init();
	s->mlx_window = mlx_new_window(s->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	s->mlx_image = mlx_new_image(s->mlx, WINDOW_X, WINDOW_Y);
	s->image_address = \
	mlx_get_data_addr(s->mlx_image, &s->bpp, &s->size_line, &s->endian);
	s->depth = VISION_DEPTH;
	s->p = p;
	s->map = p->map;
	s->map_height = p->map_h;
	s->map_width_max = p->map_w;
	s->ceiling_color = rgb_to_uint(0, p->c_color_rgb_int[0], \
	p->c_color_rgb_int[1], p->c_color_rgb_int[2]);
	s->floor_color = rgb_to_uint(0, p->f_color_rgb_int[0], \
	p->f_color_rgb_int[1], p->f_color_rgb_int[2]);
	if (p->leaf_is_here)
		sprite->position = ft_calloc_p(s->p->full_sprite_count, \
		sizeof(t_coord));
	s->sprite = sprite;
	assign_rgb_color(171, 174, 176, &s->fog);
	assign_rgb_color(57, 57, 57, &s->minimap_color);
	assign_rgb_color(0, 0, 0, &s->black);
	load_textures(p, s);
	set_defult_setting(s);
}

int	main(int argc, char **argv)
{
	t_sprite	sprite;
	t_main		s;
	t_pars		p;

	parse(argc, argv, &p);
	initiate_main_struct(&s, &p, &sprite);
	initiate_player_info(&s);
	mlx_put_image_to_window(s.mlx, s.mlx_window, s.start_screen.image, 0, 0);
	mlx_hook(s.mlx_window, 2, 0, key_hooks, &s);
	mlx_hook(s.mlx_window, 6, 0, mouse_perspective, &s);
	mlx_hook(s.mlx_window, 17, 0, close_x, &s);
	mlx_loop_hook(s.mlx, animation, &s);
	mlx_loop(s.mlx);
}
