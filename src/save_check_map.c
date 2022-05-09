/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_check_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:49:27 by Alia              #+#    #+#             */
/*   Updated: 2022/05/09 21:25:56 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_str_isrgb(char *str)
{
	int	i;
	int	comma_count;
	int	digit_count;

	i = 0;
	comma_count = 0;
	digit_count = 0;
	while (str[i])
	{
		if (str[i] == ',' && ft_isdigit(str[i + 1]))
		{
			digit_count = 0;
			comma_count++;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		if (digit_count > 3 || comma_count > 2)
			return (false);
		digit_count++;
		i++;
	}
	return (true);
}

void	check_file_validity(t_pars *p)
{
	if (!p->n || !p->s || !p->w || !p->e || !p->f || !p->c || p->extra || \
	ft_str_isrgb(p->f_color_rgb) == false || \
	ft_str_isrgb(p->c_color_rgb) == false)
	{
		printf("%soooi .. fix your shit%s\n", RED, RESET);
		// printf("%sError: check map%s\n", RED, RESET);
		free_char_double_pointer(p->full_file);
		exit(0);
	}
	rgb_char_to_int(p->f_color_rgb, p->f_color_rgb_int);
	rgb_char_to_int(p->c_color_rgb, p->c_color_rgb_int);
	if (p->f_color_rgb_int[0] > 255 || p->f_color_rgb_int[1] > 255 || \
	p->f_color_rgb_int[2] > 255 || p->c_color_rgb_int[0] > 255 || \
	p->c_color_rgb_int[1] > 255 || p->c_color_rgb_int[2] > 255)
	{
		printf("%soooi .. fix your shit%s\n", RED, RESET);
		// printf("%sError: check map%s\n", RED, RESET);
		free_char_double_pointer(p->full_file);
		exit(0);
	}
}

void	get_map_x_y(t_pars *p)
{
	int	i;

	i = 0;
	p->map_h = p->file_h - p->map_starting_i;
	while (i < p->map_h)
	{
		if (!p->map[i][0])
			p->map_error = true;
		if (p->map_w < (int)ft_strlen(p->map[i]))
			p->map_w = ft_strlen(p->map[i]);
		i++;
	}
}

void	check_map_surrounding(t_pars *p)
{
	int	x;
	int	y;
	
	y = -1;
	while (p->map[++y])
	{
		x = -1;
		while (p->map[y][++x])
		{
			if ((!y || !x || x == (int)ft_strlen(p->map[y]) - 1 || !p->map[y + 1]) && (p->map[y][x] != '1' && p->map[y][x] != ' '))
				p->map_error = true;
			else if (((p->map[y + 1] && x >= (int)ft_strlen(p->map[y + 1])) || (y && x >= (int)ft_strlen(p->map[y - 1]))) && (p->map[y][x] != '1' && p->map[y][x] != ' '))
				p->map_error = true;
			else if (p->map[y][x] == ' ')
			{
				if (x && p->map[y][x - 1] != '1' && p->map[y][x - 1] != ' ')
						p->map_error = true;
				else if (p->map[y][x + 1] && p->map[y][x + 1] != '1' && p->map[y][x + 1] != ' ')
					p->map_error = true;
				else if (y && x < (int)ft_strlen(p->map[y - 1]) && p->map[y - 1][x] != '1' && p->map[y - 1][x] != ' ')
					p->map_error = true;
				else if (p->map[y + 1] && x < (int)ft_strlen(p->map[y + 1]) && p->map[y + 1][x] != '1' && p->map[y + 1][x] != ' ')
					p->map_error = true;
			}
			if (p->map_error)
				return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_pars	p;

	ft_bzero(&p, sizeof(t_pars));
	user_input_check(argc, argv);
	init_map_save(argv[1], &p);
	check_file_validity(&p);
	rgb_to_hex(p.f_color_rgb_int, p.f_color_hex);
	rgb_to_hex(p.c_color_rgb_int, p.c_color_hex);
	p.map = &p.full_file[p.map_starting_i];
	get_map_x_y(&p);
	check_map_surrounding(&p);
	if (p.map_error)
	{
		printf("%soooi .. fix your shit%s\n", RED, RESET);
		// printf("%sError: check map%s\n", RED, RESET);
		free_char_double_pointer(p.full_file);
		exit(0);
	}
	/* ----------------------- testing ---------------------- */
	printf("%syaaaay! no errors%s\n", GREEN1, RESET);

	printf("%sint: %d,%d,%d%s\n", YELLOW1, p.f_color_rgb_int[0], p.f_color_rgb_int[1], p.f_color_rgb_int[2], RESET);
	printf("%schar: %s%s\n", LIGHT_BLUE1, p.f_color_hex, RESET);

	printf("%sint: %d,%d,%d%s\n", YELLOW1, p.c_color_rgb_int[0], p.c_color_rgb_int[1], p.c_color_rgb_int[2], RESET);
	printf("%schar: %s%s\n", LIGHT_BLUE1, p.c_color_hex, RESET);
	for (int i = 0; i < p.map_h; i++)
		printf("%s.%s.%s\n", PURPLE1, p.map[i], RESET);
	// printf("%s*%s*%s\n", BLUE1, p.f_color_rgb, RESET);
	// printf("%s*%s*%s\n", BLUE1, p.c_color_rgb, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.s_texture, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.n_texture, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.w_texture, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.e_texture, RESET);

}