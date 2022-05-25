/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:15 by anasr             #+#    #+#             */
/*   Updated: 2022/05/25 18:54:11 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/* function to free double char pointer */
void	free_double_char(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = 0;
	return ;
}

/* function to exit the program */
int	close_x(t_main *s)
{
	int	i;
	
	//destroy textures
	mlx_destroy_image(s->mlx, s->start_screen.image);
	mlx_destroy_image(s->mlx, s->end_screen.image);
	mlx_destroy_image(s->mlx, s->texture[0].image);
	mlx_destroy_image(s->mlx, s->texture[1].image);
	mlx_destroy_image(s->mlx, s->texture[2].image);
	mlx_destroy_image(s->mlx, s->texture[3].image);
	i = -1;
	while (++i < 9)
		mlx_destroy_image(s->mlx, s->leaf_dude[i].image);
	if (s->p->c_is_texture)
		mlx_destroy_image(s->mlx, s->ceiling_tex.image);
	if (s->p->f_is_texture)
		mlx_destroy_image(s->mlx, s->floor_tex.image);
	
	//destroy main image
	mlx_destroy_image(s->mlx, s->mlx_image);

	//destroy window
	mlx_destroy_window(s->mlx, s->mlx_window);

	//free allocations
	free_double_char(s->p->full_file);
	free(s->sprite->position);
	exit(1);
}