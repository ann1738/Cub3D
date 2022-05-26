/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:03:03 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 18:10:29 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_tex(t_texture *texture, char *tex_file_path, t_main *s)
{
	texture->image = mlx_xpm_file_to_image(s->mlx, tex_file_path, \
	&texture->width, &texture->height);
	texture->image_address = mlx_get_data_addr(texture->image, &texture->bpp, \
	&texture->size_line, &texture->endian);
}

static	void	load_leaf_tex(t_main *s)
{
	load_single_tex(&s->leaf_dude[0], "./textures/leaf_dude/L1.xpm", s);
	load_single_tex(&s->leaf_dude[1], "./textures/leaf_dude/L2.xpm", s);
	load_single_tex(&s->leaf_dude[2], "./textures/leaf_dude/L3.xpm", s);
	load_single_tex(&s->leaf_dude[3], "./textures/leaf_dude/L4.xpm", s);
	load_single_tex(&s->leaf_dude[4], "./textures/leaf_dude/L5.xpm", s);
	load_single_tex(&s->leaf_dude[5], "./textures/leaf_dude/L6.xpm", s);
	load_single_tex(&s->leaf_dude[6], "./textures/leaf_dude/L7.xpm", s);
	load_single_tex(&s->leaf_dude[7], "./textures/leaf_dude/L8.xpm", s);
	s->leaf_dude[8].image = \
	mlx_xpm_file_to_image(s->mlx, "./textures/leaf_dude/leaf_c.xpm", \
	&s->leaf_dude[8].width, &s->leaf_dude[8].height);
}

void	load_textures(t_pars *p, t_main *s)
{
	load_single_tex(&s->texture[0], p->n_texture, s);
	load_single_tex(&s->texture[1], p->s_texture, s);
	load_single_tex(&s->texture[2], p->w_texture, s);
	load_single_tex(&s->texture[3], p->e_texture, s);
	load_single_tex(&s->start_screen, START_SCREEN_PATH, s);
	load_single_tex(&s->end_screen, END_SCREEN_PATH, s);
	if (s->p->f_is_texture)
		load_single_tex(&s->floor_tex, p->f_color_rgb, s);
	if (s->p->c_is_texture)
		load_single_tex(&s->ceiling_tex, p->c_color_rgb, s);
	if (s->p->leaf_is_here)
		load_leaf_tex(s);
}
