/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:49:27 by Alia              #+#    #+#             */
/*   Updated: 2022/05/26 17:46:27 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_n_other_map_content(t_pars *p, int x, int y, int *p_count)
{
	if (p->map[y][x] == 'N' || p->map[y][x] == 'S' || \
	p->map[y][x] == 'E' || p->map[y][x] == 'W')
		(*p_count)++;
	else if (p->map[y][x] == 'L')
	{
		p->full_sprite_count++;
		p->leaf_is_here = true;
	}
	else if (p->map[y][x] != '1' && p->map[y][x] != '0' && \
	p->map[y][x] != ' ' && p->map[y][x] != 'N' && \
	p->map[y][x] != 'S' && p->map[y][x] != 'E' && p->map[y][x] != 'W' && \
	p->map[y][x] != 'L')
		p->map_error = true;
}

static void	must_be_sp_or_1(t_pars *p, int x, int y, int *p_count)
{
	if ((!y || !x || x == (int)ft_strlen(p->map[y]) - 1 || !\
	p->map[y + 1]) && (p->map[y][x] != '1' && p->map[y][x] != ' '))
		p->map_error = true;
	else if (((p->map[y + 1] && x >= (int)ft_strlen(p->map[y + 1])) || \
	(y && x >= (int)ft_strlen(p->map[y - 1]))) && \
	(p->map[y][x] != '1' && p->map[y][x] != ' '))
		p->map_error = true;
	else if (p->map[y][x] == ' ')
	{
		if (x && p->map[y][x - 1] != '1' && p->map[y][x - 1] != ' ')
				p->map_error = true;
		else if (p->map[y][x + 1] && p->map[y][x + 1] != '1' && \
		p->map[y][x + 1] != ' ')
			p->map_error = true;
		else if (y && x < (int)ft_strlen(p->map[y - 1]) && \
		p->map[y - 1][x] != '1' && p->map[y - 1][x] != ' ')
			p->map_error = true;
		else if (p->map[y + 1] && x < (int)ft_strlen(p->map[y + 1]) && \
		p->map[y + 1][x] != '1' && p->map[y + 1][x] != ' ')
			p->map_error = true;
	}
	else
		player_n_other_map_content(p, x, y, p_count);
}

void	check_map_content(t_pars *p)
{
	int	x;
	int	y;
	int	player_count;

	y = -1;
	player_count = 0;
	p->map_h = p->file_h - p->map_starting_i;
	while (p->map[++y])
	{
		x = -1;
		while (p->map[y][++x])
		{
			must_be_sp_or_1(p, x, y, &player_count);
			if (p->map_error)
				return ;
		}
		if (!x && !p->map[y][x])
			p->map_error = true;
		else if (p->map_w < x)
			p->map_w = x;
	}
	if (player_count != 1)
		p->map_error = true;
}
