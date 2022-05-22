/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:03:03 by ann               #+#    #+#             */
/*   Updated: 2022/05/22 18:26:03 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_texture(t_texture *texture, char *tex_file_path, t_main *s)
{
	texture->image = mlx_xpm_file_to_image(s->mlx, tex_file_path, &texture->width, &texture->height);
	texture->image_address = mlx_get_data_addr(texture->image, &texture->bpp, &texture->size_line, &texture->endian);
}

void	load_textures(t_pars *p, t_main *s)
{
	/* when floor and ceiling textures are added, i recommend adding a flag */
	/* to check if the floor and ceiling are textures or colors and then */
	/* the count needs to be increased from 4 */

	/*NORTH SOUTH WEST EAST order of array*/
	load_single_texture(&s->texture[0], p->n_texture, s);
	load_single_texture(&s->texture[1], p->s_texture, s);
	load_single_texture(&s->texture[2], p->w_texture, s);
	load_single_texture(&s->texture[3], p->e_texture, s);
	if (s->p->full_sprite_count)
		load_single_texture(&s->texture[4], "./textures/Leaf_Dude.xpm", s);		
}