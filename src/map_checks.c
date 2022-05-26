/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:49:27 by Alia              #+#    #+#             */
/*   Updated: 2022/05/26 15:00:27 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_str_isrgb(char *str)
{
	int	i;
	int	comma_count;
	int	digit_count;

	i = -1;
	comma_count = 0;
	digit_count = 0;
	while (str[++i])
	{
		if (str[i] == ',' && ft_isdigit(str[i + 1]))
		{
			if (!digit_count)
				return (false);
			digit_count = 0;
			comma_count++;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		if (digit_count > 3 || comma_count > 2)
			return (false);
		digit_count++;
	}
	if (comma_count != 2)
		return (false);
	return (true);
}

void	check_textures_validity(t_pars *p)
{
	ft_open(p->n_texture);
	ft_open(p->s_texture);
	ft_open(p->e_texture);
	ft_open(p->w_texture);
	if (p->f_is_texture)
		ft_open(p->f_color_rgb);
	if (p->c_is_texture)
		ft_open(p->c_color_rgb);
}

void	check_file_validity(t_pars *p)
{
	if (ft_strchr(p->f_color_rgb, '/'))
		p->f_is_texture = true;
	if (ft_strchr(p->c_color_rgb, '/'))
		p->c_is_texture = true;
	if (!p->n || !p->s || !p->w || !p->e || !p->f || !p->c || p->extra || \
	(!p->f_is_texture && ft_str_isrgb(p->f_color_rgb) == false )|| \
	(!p->c_is_texture && ft_str_isrgb(p->c_color_rgb) == false))
	{
		printf("%sError: check map%s\n", RED, RESET);
		free_char_double_pointer(p->full_file);
		exit(1);
	}
	check_textures_validity(p);
	if (!p->f_is_texture)
	{
		rgb_char_to_int(p->f_color_rgb, p->f_color_rgb_int);
		if (p->f_color_rgb_int[0] > 255 || p->f_color_rgb_int[1] > 255 || \
		p->f_color_rgb_int[2] > 255)
		{
			printf("%sError: check map%s\n", RED, RESET);
			free_char_double_pointer(p->full_file);
			exit(1);
		}
	}
	if (!p->c_is_texture)
	{
		rgb_char_to_int(p->c_color_rgb, p->c_color_rgb_int);
		if (p->c_color_rgb_int[0] > 255 || p->c_color_rgb_int[1] > 255 || \
		p->c_color_rgb_int[2] > 255)
		{
			printf("%sError: check map%s\n", RED, RESET);
			free_char_double_pointer(p->full_file);
			exit(1);
		}
	}
}

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
	p->map[y][x] != 'S' && p->map[y][x] != 'E' && p->map[y][x] != 'W' && p->map[y][x] != 'L')
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
