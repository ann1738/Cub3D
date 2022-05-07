/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:58:57 by ann               #+#    #+#             */
/*   Updated: 2022/05/07 01:12:13 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_struct(t_main *s)
{	
	s->mlx = mlx_init();
	s->mlx_window = mlx_new_window(s->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	s->mlx_image = mlx_new_image(s->mlx, WINDOW_X, WINDOW_Y);
	s->image_address = mlx_get_data_addr(s->mlx_image, &s->bpp, &s->size_line, &s->endian);
	mlx_do_key_autorepeatoff(s->mlx);
	mlx_do_key_autorepeaton(s->mlx);
}

void	temp_parse(char *path, t_main *s)
{
	s->map_width = get_x(path);
	s->map = save_map(s->map, path, s->map_width);
	s->map_height = get_y(s->map);
}

int main(int argc, char **argv)
{
	t_main	s;

	if (argc != 2)
		return (write(2, "Invalid\n", 8));
	ft_bzero(&s, sizeof(t_main));
	init_struct(&s);
	temp_parse(argv[1], &s);
	draw_minimap(&s);

	mlx_put_image_to_window(s.mlx, s.mlx_window, s.mlx_image, 0, 0);
	mlx_key_hook(s.mlx_window, key_hooks, &s);
	mlx_hook(s.mlx_window, 17, 0, close_x, &s);
	mlx_loop(s.mlx);
}