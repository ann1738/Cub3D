/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:15 by anasr             #+#    #+#             */
/*   Updated: 2022/05/25 18:34:12 by aalsuwai         ###   ########.fr       */
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
	mlx_destroy_image(s->mlx, s->texture[0].image);
	mlx_destroy_image(s->mlx, s->texture[1].image);
	mlx_destroy_image(s->mlx, s->texture[2].image);
	mlx_destroy_image(s->mlx, s->texture[3].image);
	//destroy ceiling and floor with if condition ( and door if used)
	mlx_destroy_image(s->mlx, s->mlx_image);
	mlx_destroy_window(s->mlx, s->mlx_window);
	free_double_char(s->p->full_file);
	//free allocations
	exit(1);
}