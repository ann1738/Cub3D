/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_validity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:31:27 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/26 19:52:12 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_str_isrgb(char *str)
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

static void	throw_map_error_n_exit(t_pars *p)
{
	printf("%sError: check map%s\n", RED, RESET);
	free_char_double_pointer(p->full_file);
	exit(1);
}

static void	check_textures_validity(t_pars *p)
{
	if (!has_dot_xpm(p->e_texture) || !has_dot_xpm(p->w_texture) \
	|| !has_dot_xpm(p->n_texture) || !has_dot_xpm(p->s_texture) || \
	(p->f_is_texture && !has_dot_xpm(p->f_color_rgb)) || \
	(p->c_is_texture && !has_dot_xpm(p->f_color_rgb)))
		throw_map_error_n_exit(p);
	close(ft_open_n_free(p, p->n_texture));
	close(ft_open_n_free(p, p->s_texture));
	close(ft_open_n_free(p, p->e_texture));
	close(ft_open_n_free(p, p->w_texture));
	if (p->f_is_texture)
		close(ft_open_n_free(p, p->f_color_rgb));
	if (p->c_is_texture)
		close(ft_open_n_free(p, p->c_color_rgb));
}

void	check_file_validity(t_pars *p)
{
	if (ft_strchr(p->f_color_rgb, '/'))
		p->f_is_texture = true;
	if (ft_strchr(p->c_color_rgb, '/'))
		p->c_is_texture = true;
	if (!p->n || !p->s || !p->w || !p->e || !p->f || !p->c || p->extra || \
	(!p->f_is_texture && ft_str_isrgb(p->f_color_rgb) == false) || \
	(!p->c_is_texture && ft_str_isrgb(p->c_color_rgb) == false))
		throw_map_error_n_exit(p);
	check_textures_validity(p);
	if (!p->f_is_texture)
	{
		rgb_char_to_int(p->f_color_rgb, p->f_color_rgb_int);
		if (p->f_color_rgb_int[0] > 255 || p->f_color_rgb_int[1] > 255 || \
		p->f_color_rgb_int[2] > 255)
			throw_map_error_n_exit(p);
	}
	if (!p->c_is_texture)
	{
		rgb_char_to_int(p->c_color_rgb, p->c_color_rgb_int);
		if (p->c_color_rgb_int[0] > 255 || p->c_color_rgb_int[1] > 255 || \
		p->c_color_rgb_int[2] > 255)
			throw_map_error_n_exit(p);
	}
}
